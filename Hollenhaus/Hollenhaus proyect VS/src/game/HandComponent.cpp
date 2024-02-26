#include "HandComponent.h"
#include "Manager.h"
#include "Entity.h"
#include "SpriteRenderer.h"

HandComponent::HandComponent() :
	transform_(),
	numCards_(0)
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

	if (numCards_ < MAX_HAND_CARDS)
	{

		card->getComponent<Transform>()->addParent(transform_);
		card->getComponent<Transform>()->getRelativeScale().set(.25, .25);
		card->getComponent<Transform>()->getRelativePos().set(0, 0);
		card->getComponent<SpriteRenderer>()->setTexture("hand");
		cardsInHand_.push_back(card);
		refreshPositions();
		//transform_->getGlobalAngle() = 90;
		return true;
	}
	return false;
}

void HandComponent::refreshPositions() {
	std::cout << (1 + "");
	for (int i = 0; i < cardsInHand_.size(); i++)
	{
		//TuVieja("Aaa");
		//float posx = cardsInHand_[i]->getComponent<Transform>()->getRelativePos().getX() + (i * 10);
		//cardsInHand_[i]->getComponent<Transform>()->getRelativePos().setX(posx);
		//cardsInHand_[i]->getComponent<Transform>()->getGlobalAngle() = calculateAngle(i);

		// Ecuaciones del semi circulo?
		cardsInHand_[i]->getComponent<Transform>()->getRelativePos().set(
			100 * cos((((360 / MAX_HAND_CARDS) * i)) + 180),
			100 * sin(((360 / MAX_HAND_CARDS) * i)) + 180);

		// Ecuaciones del circulo
		/*cardsInHand_[i]->getComponent<Transform>()->getRelativePos().set(
			100 * cos(((360 / cardsInHand_.size()) * i) + 90),
			100 * sin(((360 / cardsInHand_.size()) * i) + 90));*/
	}
}

float HandComponent::calculateAngle(int numCarta) {
	float angle = (110 / cardsInHand_.size()) * numCarta;
	return angle;// -(110 / ;
}