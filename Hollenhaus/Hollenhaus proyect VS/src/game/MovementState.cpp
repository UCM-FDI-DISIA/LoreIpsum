#include "MovementState.h"

MovementState::MovementState() {

}
void MovementState::update()
{
	GameState::update();
}

void MovementState::render() const
{
	GameState::render();
}

void MovementState::refresh()
{
	GameState::refresh();
}

void MovementState::onEnter() const
{
	//-----Ciudad provisional de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudad");
	fondo->getComponent<Transform>()->getGlobalScale().set(2.0f, 1.0f);
	fondo->getComponent<Transform>()->getGlobalPos().set(0, 0);
	//fondo->addComponent<MoveOnClick>();
}

void MovementState::onExit() const
{
}
