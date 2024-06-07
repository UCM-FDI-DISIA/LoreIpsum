#include <../pchs/pch.h>

#include "Solitaire.h"
#include "../components/managers/Manager.h"
#include "../components/ShineComponent.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"
#include "../components/Button.h"
#include "../../sdlutils/RandomNumberGenerator.h"
#include "../SoundManager.h"

// Factorias:
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"
#include "game/components/Clickable.h"

Solitaire::Solitaire()
{

}

void Solitaire::update()
{
	GameState::update();

}

void Solitaire::render() const
{
	GameState::render();

}

void Solitaire::refresh()
{
	GameState::refresh();

}

void Solitaire::onEnter()
{
	
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("greenTable");
	fondo->getComponent<Transform>()->setGlobalScale(0.70f, 0.70f);
	fondo->setLayer(0);

	

}

void Solitaire::onExit()
{
}