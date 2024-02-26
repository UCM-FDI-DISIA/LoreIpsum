#include "LuisState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

#include "BoardFactory.h"

LuisState::LuisState() : GameState() {


	CardFactory_v0* factory = new CardFactory_v0();
	BoardFactory* boardFactory = new BoardFactory(4, 4);
	boardFactory->createBoard();
	factory->createHand();
	//card->setLayer(1);

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
}

LuisState::~LuisState()
{

}

void LuisState::refresh()
{
	GameState::refresh();
}

void LuisState::update()
{
	GameState::update();

}

void LuisState::render() const
{
	GameState::render();
}
