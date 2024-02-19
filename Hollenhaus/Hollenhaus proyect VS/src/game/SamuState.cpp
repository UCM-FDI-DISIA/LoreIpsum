#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"


#include "ComponentRender.h"
#include "../Transform.h"

SamuState::SamuState() : GameState() {

	auto mngr = GameStateMachine::instance()->getMngr();

	card = mngr->addEntity();
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
