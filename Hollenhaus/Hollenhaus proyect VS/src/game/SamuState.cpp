#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"
#include "GameState.h"

#include "../SpriteRenderer.h"
#include "../Transform.h"
#include "../BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"

SamuState::SamuState() {

	auto mngr = GameStateMachine::instance()->getMngr();

	card = mngr->addEntity();
	
	mngr->addComponent<Transform>(card);
	mngr->addComponent<SpriteRenderer>(card, "card");
	mngr->addComponent<BoxCollider>(card);
	mngr->addComponent<Drag>(card);
	mngr->addComponent<CardStateManager>(card);

	auto cardTransform = mngr->getComponent<Transform>(card);

	cardTransform->getGlobalScale().set(0.4, 0.4);
	cardTransform->getGlobalPos().set(100, 100);	

	auto cardDrag = mngr->getComponent<Drag>(card);


	cardDrag->addCondition([this]() {
			auto mngr =  GameStateMachine::instance()->getMngr(); 
			
			auto state = mngr->getComponent<CardStateManager>(card)->getState();

			return state == CardStateManager::ON_HAND;
		});

	auto cardCardStateManager = mngr->getComponent<CardStateManager>(card);

	cardCardStateManager->setState(CardStateManager::ON_HAND);
}

SamuState::~SamuState()
{

}

void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	GameState::update();

	
}

void SamuState::render() const
{
	GameState::render();
}
