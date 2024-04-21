#include <../pchs/pch.h>
#include "KeyMenuState.h"

#include "game/components/Button.h"
#include "game/components/KeyComponent.h"

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
	ecs::entity_t key = Instantiate(Vector2D(200, 100));
	key->addComponent<KeyComponent>(getKeys());
	key->addComponent<SpriteRenderer>("key");

	ecs::entity_t button = Instantiate(Vector2D(0, 100));
	button->addComponent<SpriteRenderer>("rice");
	button->addComponent<Button>()->connectToButton([this]() { GameStateMachine::instance()->setState(7); });
}

void KeyMenuState::onExit() 
{
	GameStateMachine::instance()->getMngr()->Free();
}
