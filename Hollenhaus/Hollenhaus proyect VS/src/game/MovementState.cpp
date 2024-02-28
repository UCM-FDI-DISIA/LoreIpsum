#include "MovementState.h"

MovementState::MovementState()
{

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
	fondo->addComponent<BoxCollider>();
	fondo->getComponent<Transform>()->getGlobalScale().set(2.0f, 1.0f);
	fondo->getComponent<Transform>()->getGlobalPos().set(50, 0); //esto no cambia nadaaa ?¿?¿¿? probar setGlobalPos
	//fondo->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	fondo->addComponent<MoveOnClick>();
}

void MovementState::onExit() const
{
}
