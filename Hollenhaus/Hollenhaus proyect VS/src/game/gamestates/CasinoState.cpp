#include <../pchs/pch.h>

#include "CasinoState.h"
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

CasinoState::CasinoState()
{

}

void CasinoState::update()
{
	GameState::update();

}

void CasinoState::render() const
{
	GameState::render();

}

void CasinoState::refresh()
{
	GameState::refresh();

}

void CasinoState::onEnter()
{
	factory = new Factory();
	factory->SetFactories(
		static_cast<NPCFactory*>(new NPCFactory_V0()));
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	/*
	
	//-----Imagen de fondo:
	fondo->addComponent<SpriteRenderer>("casino");
	fondo->getComponent<Transform>()->setGlobalScale(0.70f, 0.70f);
	fondo->setLayer(0);
	*/

	ecs::entity_t croupier = factory->createNPC(23, fondo);

	//------Boton para volver:
	ecs::entity_t exitButton = Instantiate(Vector2D(20, 20));
	exitButton->addComponent<Transform>();
	exitButton->addComponent<SpriteRenderer>("boton_flecha");
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exitButton->addComponent<Button>();
	exitButton->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(1); });
	exitButton->addComponent<Clickable>("boton_flecha", true);
	exitButton->getComponent<Transform>()->setGlobalPos(10, 10);

}

void CasinoState::onExit()
{
	std::cout << "\nEXIT CASINO.";

	saveData();

	GameStateMachine::instance()->getMngr()->Free();

	delete factory;
}
