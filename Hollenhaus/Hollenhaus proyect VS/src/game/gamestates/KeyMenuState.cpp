#include "pch.h"
#include "KeyMenuState.h"

#include "../components/managers/KeyManager.h"

KeyMenuState::KeyMenuState()
{

}

KeyMenuState::~KeyMenuState()
{

}

void KeyMenuState::refresh()
{
	GameState::refresh();
}

void KeyMenuState::update()
{
	GameState::update();
}

void KeyMenuState::render() const
{
	GameState::render();
}

void KeyMenuState::onEnter() 
{
	// Manager de la leyenda
	ecs::entity_t keyManager = Instantiate(Vector2D(200, 100));
	keyManager->addComponent<KeyManager>();
	keyManager->addComponent<SpriteRenderer>("key");
}

void KeyMenuState::onExit() 
{
	GameStateMachine::instance()->getMngr()->Free();
}
