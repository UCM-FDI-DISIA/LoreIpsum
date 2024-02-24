#include "CardFactory_v0.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"

#include "DropDetector.h"



ecs::entity_t CardFactory_v0::createCard(Vector2D pos)
{
	ecs::entity_t card = Instantiate(pos, ecs::grp::CARDS);

	card->addComponent<SpriteRenderer>("card");
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();
	
	auto cardTransform = card->getComponent<Transform>();

	cardTransform->getGlobalScale().set(cardScale, cardScale);

	/*

	auto cardDrag = mngr().getComponent<Drag>(card);

	cardDrag->addCondition([card]() {

		auto state = mngr().getComponent<CardStateManager>(card)->getState();

		return state == CardStateManager::ON_HAND;
		});
	
	*/

	auto cardCardStateManager = card->getComponent<CardStateManager>();

	cardCardStateManager->setState(CardStateManager::ON_HAND);
	
    return card;
}


ecs::entity_t CardFactory_v0::createDropDetector(Vector2D pos)
{	
	ecs::entity_t dropDect = Instantiate(ecs::grp::DROPS);

	dropDect->addComponent<Transform>()->getGlobalPos().set(pos);
	dropDect->addComponent<BoxCollider>();
	dropDect->addComponent<DropDetector>()->getCardPos().set(pos);

	dropDect->getComponent<BoxCollider>()->setSize(
							Vector2D(sdlutils().images().at("card").width()*cardScale,
											(sdlutils().images().at("card").height())*cardScale )) ;

	return dropDect;
}

void CardFactory_v0::createBoard()
{

	float initX = 200;
	float initY = 20;
	float xOffset = 82;
	float yOffset = 120;


	createDropDetector(Vector2D(initX, initY));
	createDropDetector(Vector2D(initX +xOffset, initY));
	createDropDetector(Vector2D(initX + (2*xOffset),initY));


	createDropDetector(Vector2D(initX, initY + yOffset));
	createDropDetector(Vector2D(initX + xOffset, initY+yOffset));
	createDropDetector(Vector2D(initX + (2 * xOffset), initY+yOffset));


	createDropDetector(Vector2D(initX, initY +(2*yOffset)));
	createDropDetector(Vector2D(initX + xOffset, initY + (2 * yOffset)));
	createDropDetector(Vector2D(initX + (2 * xOffset), initY + (2 * yOffset)));
}

void CardFactory_v0::createHand()
{
	int initY = 400;
	int initX = 200;
	int offSetX = 50;
	
	createCard(Vector2D(initX, initY))->setLayer(1);
	createCard(Vector2D(initX + offSetX, initY))->setLayer(1);
	createCard(Vector2D(initX + offSetX*2, initY))->setLayer(2);
	createCard(Vector2D(initX + offSetX*3, initY))->setLayer(1);
}

