#include <../pchs/pch.h>

#include "HandComponent.h"
#include "managers/Manager.h"
#include "../Entity.h"
#include "basics/SpriteRenderer.h"
#include "managers/CardStateManager.h"

#include "Card.h"
#include "basics/TextComponent.h"
#include "managers/DragManager.h"

HandComponent::HandComponent() :
	transform_(), lastCardAdded_(nullptr)
{

}
HandComponent::~HandComponent() {

}

void HandComponent::initComponent() {

	transform_ = ent_->getComponent<Transform>();
	transform_->getGlobalPos().set(400, 400);
}

void HandComponent::addCard(ecs::entity_t card) {

	auto cardCardStateManager = card->getComponent<CardStateManager>();
	cardCardStateManager->setState(Cards::ON_HAND);

	if (owner_ == Players::IA)
	{
		card->getComponent<Transform>()->setGlobalAngle(180.0f);
	}

	card->getComponent<Transform>()->addParent(transform_);

	card->getComponent<Transform>()->setGlobalScale(Vector2D(cardScale_, cardScale_));

	//card->getComponent<Transform>()->getRelativeScale().set(cardScale_, cardScale_);

	if (lastCardAdded_ != nullptr)
		card->setLayer(lastCardAdded_->getLayer() + 3); // COSITAS DEL ORDER IN LAYER :D (JIMBO)
	else
		card->setLayer(1);
	card->getComponent<Transform>()->increaseLayer(card->getLayer());


	// card->setLayer(1);

	// Settea tamano de carta para anadir cartas directamente desde la factoria
	cardsInHand_.push_back(card);
	lastCardAdded_ = card;
	//card->setLayer(cardsInHand_.size());

	//Aquí se calcula la posición a la que tiene que llegar, no se bien como implementarlo en el tween
	refreshPositions();
	if (owner_ == Players::PLAYER1) {
		///Tween
		carta = card;
		tweenDrawCard =
			tweeny::from(card->getComponent<Transform>()->getGlobalPos().getX() + 250)
			.to(card->getComponent<Transform>()->getGlobalPos().getX())
			.during(60)
			.via(tweeny::easing::sinusoidalInOut);
		tween = true;
	}
	
}

void HandComponent::update()
{
	//Habría que hacer cuando esté el tween definitivo que cuando 
	// llegue al sitio en el que se tiene que quedar ponga el bool a falso
	if (tween && owner_ == Players::PLAYER1) {
		/// TWEENS???
		//Habría que hacer que comience en el mazo y se mueva hasta su posición
		auto drag = mngr_->getHandler(ecs::hdlr::DRAG_MANAGER)->getComponent<DragManager>();
		tweenDrawCard.step(1);
		if (tweenDrawCard.progress() == 1.0) tween = false;
		if (tweenDrawCard.peek() > 0) // una mierda de manera de 1. saber que devuelve un int valido 2. que no se salga
		{
			if (drag != nullptr) drag->setDraggable(false);
			Vector2D step(
				tweenDrawCard.peek(),
				carta->getComponent<Transform>()->getGlobalPos().getY()
			);
			carta->getComponent<Transform>()->setGlobalPos(step);
		}
		if (tweenDrawCard.progress() == 1.0)
		{
			tween = false;
			if (drag != nullptr) drag->setDraggable(true);
		}
	}
	
}

void HandComponent::removeCard(ecs::entity_t card) {
	bool found = false;

	std::vector<ecs::entity_t> auxVec;

	// Guarda en el vector auxiliar las cartas que siguen en la mano, y quita el parent a la que ya no esta en la mano
	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		if (cardsInHand_[i] != card)
		{ // la carta esta en la manita del fantasmiko
			auxVec.push_back(cardsInHand_[i]);
			//numCards_++;
			transform_->getGlobalPos().getX() + 10;
		}
		else // la carta es jugada
		{
			// cambia la escala para ajustarse a la celda del tablero
			card->getComponent<Transform>()->setGlobalScale(cardScaleBoard_, cardScaleBoard_);

			// ajusta tambien los textos
			for (auto child : card->getComponent<Transform>()->getChildren())
			{
				auto texto = child->getEntity()->getComponent<TextComponent>();
				if (texto != nullptr)
				{
					texto->setFont("8bit_size_16");
					child->getRelativePos().set(
						child->getRelativePos().getX(), 
						child->getRelativePos().getY()-child->getRelativePos().getY()/6.25
					);
				}
			}

			// su parent ya no es la mano izq
			cardsInHand_[i]->getComponent<Transform>()->removeParent();
		}
	}

	cardsInHand_.clear();
	cardsInHand_ = auxVec;

	refreshPositions();
}

std::vector<Card*> HandComponent::getHand()
{
	std::vector<Card*> v;

	for (auto e : cardsInHand_) {
		v.push_back(new Card((*e->getComponent<Card>())));//copia para no usar la misma memoria?
	}

	return v;
}

int HandComponent::indexOf(ecs::entity_t c)
{
	auto it = std::find(cardsInHand_.begin(), cardsInHand_.end(), c);

	return it == cardsInHand_.end() ? -1 : it - cardsInHand_.begin();
}

void HandComponent::refreshPositions() {
	std::vector<Vector2D>positions;

	const int sign = downwards_ ? 1 : -1;

	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		// y = (x^2)/CARD_SEPARATION
		int x = ((i - cardsInHand_.size() / 2) * CARD_SEPARATION);

		//Posición de la carta (El vector 2D)
		positions.push_back(Vector2D(x, pow(x, 2) / (ARCH_AMPLITUDE * sign)));
	}

	for (int i = 0; i < cardsInHand_.size(); i++)
	{

		// Ecuacion de la parabola que forma las cartas
		cardsInHand_[i]->getComponent<Transform>()->getRelativePos().set(positions[i]);
	}
}