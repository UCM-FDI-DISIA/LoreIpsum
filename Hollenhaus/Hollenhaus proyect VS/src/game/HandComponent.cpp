#include "HandComponent.h"
#include "Manager.h"
#include "Entity.h"
#include "SpriteRenderer.h"

HandComponent::HandComponent() :
	transform_()
{

}/*
HandComponent::~HandComponent() {

}
*/
void HandComponent::initComponent() {

	transform_ = ent_->getComponent<Transform>();
	transform_->getGlobalPos().set(400, 400);
}

void HandComponent::update() {


}


bool HandComponent::addCard(ecs::entity_t card) {

	if (cardsInHand_.size() < MAX_HAND_CARDS)
	{

		card->getComponent<Transform>()->addParent(transform_);
		// Settea tamano de carta para anadir cartas directamente desde la factoria
		card->getComponent<Transform>()->getRelativeScale().set(cardScale_, cardScale_);
		cardsInHand_.push_back(card);
		refreshPositions();
		return true;
	}
	return false;
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
}

void HandComponent::refreshPositions() {

	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		int x = (i-cardsInHand_.size()/2) * CARD_SEPARATION;

		// Ecuacion de la parabola que forma las cartas
		cardsInHand_[i]->getComponent<Transform>()->getRelativePos().set(
			x, pow(x,2)/(ARCH_AMPLITUDE));
	}
}