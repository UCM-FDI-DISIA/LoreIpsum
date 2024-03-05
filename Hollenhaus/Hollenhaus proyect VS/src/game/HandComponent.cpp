#include "HandComponent.h"
#include "Manager.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include "CardStateManager.h"

HandComponent::HandComponent() :
	transform_()
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
	cardCardStateManager->setState(CardStateManager::ON_HAND);


	card->getComponent<Transform>()->addParent(transform_);
	card->getComponent<Transform>()->getRelativeScale().set(cardScale_, cardScale_);
	// Settea tamano de carta para anadir cartas directamente desde la factoria
	cardsInHand_.push_back(card);
	//card->setLayer(cardsInHand_.size());
	refreshPositions();
}

void HandComponent::removeCard(ecs::entity_t card) {
	bool found = false;

	std::vector<ecs::entity_t> auxVec;

	// Guarda en el vector auxiliar las cartas que siguen en la mano, y quita el parent a la que ya no esta en la mano
	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		if (cardsInHand_[i] != card)
		{
			auxVec.push_back(cardsInHand_[i]);
			//numCards_++;
			transform_->getGlobalPos().getX() + 10;
		}
		else
		{
			card->getComponent<Transform>()->getGlobalScale().set(cardScale_, cardScale_);
			cardsInHand_[i]->getComponent<Transform>()->removeParent();
		}
	}

	cardsInHand_.clear();
	cardsInHand_ = auxVec;

	refreshPositions();
}

void HandComponent::refreshPositions() {
	std::vector<Vector2D>positions;

	const int sign = downwards ? 1 : -1;

	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		// y = (x^2)/CARD_SEPARATION
		int x = ((i - cardsInHand_.size() / 2) * CARD_SEPARATION);

		positions.push_back(Vector2D(x, pow(x, 2) / (ARCH_AMPLITUDE * sign)));
	}

	for (int i = 0; i < cardsInHand_.size(); i++)
	{

		// Ecuacion de la parabola que forma las cartas
		cardsInHand_[i]->getComponent<Transform>()->getRelativePos().set(positions[i]);
	}
}