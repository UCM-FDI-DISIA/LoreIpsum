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
    ecs::entity_t card = mngr().addEntity(ecs::grp::CARDS);
	
	card->addComponent<Transform>();
	card->addComponent<SpriteRenderer>("card");
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();


	//GameStateMachine::instance()->getMngr()->addComponent<Transform>(card);
	//mngr().addComponent<Transform>(card);
	//mngr().addComponent<SpriteRenderer>(card, "card");
	//mngr().addComponent<BoxCollider>(card);
	//mngr().addComponent<Drag>(card);
	//mngr().addComponent<CardStateManager>(card);

	
	auto cardTransform = mngr().getComponent<Transform>(card);

	cardTransform->getGlobalScale().set(0.4, 0.4);
	cardTransform->getGlobalPos().set(100, 100);

	auto cardDrag = mngr().getComponent<Drag>(card);
	



	/*
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

