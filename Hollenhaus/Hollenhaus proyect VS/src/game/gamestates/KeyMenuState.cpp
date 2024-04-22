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
	for (int i = 0; i < 6; ++i) {
		addKey();
	}
	// Leyenda
	ecs::entity_t key = Instantiate(Vector2D(200, 0));
	key->getComponent<Transform>()->setGlobalScale(0.75, 0.75);
	key->addComponent<SpriteRenderer>("key");
	key->addComponent<KeyComponent>(getKeys());

	// Boton de volver
	ecs::entity_t button = Instantiate(Vector2D(0, 0));
	button->getComponent<Transform>()->setGlobalScale(0.25, 0.25);
	button->addComponent<SpriteRenderer>("rice");
	button->addComponent<BoxCollider>();
	button->addComponent<Button>()->connectToButton([]() 
	{ 
		GameStateMachine::instance()->setState(7); 
	});
}

void KeyMenuState::onExit() 
{
	GameStateMachine::instance()->getMngr()->Free();
}
