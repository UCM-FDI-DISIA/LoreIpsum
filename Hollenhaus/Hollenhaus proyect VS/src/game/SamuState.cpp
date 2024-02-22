#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"

#include "CardFactory_v0.h"

SamuState::SamuState() : GameState() {


	CardFactory_v0* factory = new CardFactory_v0();

	card = factory->createCard();


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
