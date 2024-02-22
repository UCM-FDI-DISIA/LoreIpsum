#include "CardFactory_v0.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"

#include "DropDetector.h"



ecs::entity_t CardFactory_v0::createCard()
{
	ecs::entity_t card = Instantiate(Vector2D(100,100), ecs::grp::CARDS);

	card->addComponent<SpriteRenderer>("card");
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();
	
	auto cardTransform = card->getComponent<Transform>();

	cardTransform->getGlobalScale().set(0.4, 0.4);

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
	dropDect->addComponent<DropDetector>();

	dropDect->getComponent<BoxCollider>()->setSize(Vector2D(120,180));

	return dropDect;
}

