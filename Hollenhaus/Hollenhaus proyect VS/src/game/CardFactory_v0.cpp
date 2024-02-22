#include "CardFactory_v0.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"



ecs::entity_t CardFactory_v0::createCard()
{
    ecs::entity_t card = mngr().addEntity();

	mngr().addComponent<Transform>(card);
	mngr().addComponent<SpriteRenderer>(card, "card");
	mngr().addComponent<BoxCollider>(card);
	mngr().addComponent<Drag>(card);
	mngr().addComponent<CardStateManager>(card);

	auto cardTransform = mngr().getComponent<Transform>(card);

	cardTransform->getGlobalScale().set(0.4, 0.4);
	cardTransform->getGlobalPos().set(100, 100);

	auto cardDrag = mngr().getComponent<Drag>(card);



	cardDrag->addCondition([card]() {

		auto state = mngr().getComponent<CardStateManager>(card)->getState();

		return state == CardStateManager::ON_HAND;
		});
	

	auto cardCardStateManager = mngr().getComponent<CardStateManager>(card);

	cardCardStateManager->setState(CardStateManager::ON_HAND);


    return card;
}
