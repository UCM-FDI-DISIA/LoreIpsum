#include "SamuState.h"

#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"
#include "Entity.h"
#include "Manager.h"

#include "CardFactory_v0.h"

SamuState::SamuState() : GameState() {

	
	TuVieja("\nloading SAmuState");
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

	//std::cout << mouseRaycast()<< std::endl;
}

void SamuState::render() const
{
	GameState::render();
}

void SamuState::onEnter() const
{
	TuVieja("\nEntering in SamuState");
	//GameStateMachine::instance();
	CardFactory_v0* factory = new CardFactory_v0();

	factory->createBoard();
	factory->createHand();
	//card->setLayer(1);


	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
}

void SamuState::onExit() const
{
	TuVieja("\nExit SamuState");
}
