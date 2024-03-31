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

void MovementState::onEnter() 
{
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudadcompleta");
	fondo->addComponent<BoxCollider>();

	//tamanyo de ciudadcompleta.png: 5754 x 1212 
	fondo->getComponent<Transform>()->getGlobalScale().set(0.495f, 0.495f); //escalado para ciudadcompleta.png (porfi no toquetear)!!! 
	
	Vector2D globalPos(-1200.0f, 0); //Posición inicial de la ciudad para que se vea por el centro.
	fondo->getComponent<Transform>()->setGlobalPos(globalPos);

	//fondo->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	fondo->addComponent<MoveOnClick>(2);
}

void MovementState::onExit() 
{
	GameStateMachine::instance()->getMngr()->Free();
}
