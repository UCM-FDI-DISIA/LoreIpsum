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
	
	auto cardTransform = mngr().getComponent<Transform>(card);

	cardTransform->getGlobalScale().set(0.4, 0.4);

	/*

	auto cardDrag = mngr().getComponent<Drag>(card);

	cardDrag->addCondition([card]() {

		auto state = mngr().getComponent<CardStateManager>(card)->getState();

		return state == CardStateManager::ON_HAND;
		});
	
	*/

	auto cardCardStateManager = mngr().getComponent<CardStateManager>(card);

	cardCardStateManager->setState(CardStateManager::ON_HAND);
	
    return card;
}


ecs::entity_t CardFactory_v0::createDropDetector()
{	
	ecs::entity_t dropDect = mngr().addEntity(ecs::grp::DROPS);

	mngr().addComponent<Transform>(dropDect);
	mngr().addComponent<BoxCollider>(dropDect);
	mngr().addComponent<DropDetector>(dropDect);

	return dropDect;
}

