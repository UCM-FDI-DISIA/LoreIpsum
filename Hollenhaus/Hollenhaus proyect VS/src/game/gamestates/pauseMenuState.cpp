#include "pch.h"
#include "pauseMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"

PauseMenuState::PauseMenuState()
{
	
}

PauseMenuState::~PauseMenuState() 
{

}

void PauseMenuState::refresh()
{
	GameState::refresh();
}

void PauseMenuState::update() {}

void PauseMenuState::render() const {}

void PauseMenuState::onEnter()
{
	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });

	// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GetLastState()); // Lleva a la oficina (2).
	exit->setLayer(5);

	std::cout << "\nENTER PAUSE.\n";

	sdlutils().virtualTimer().pause();
}

void PauseMenuState::onExit()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().PAUSEKEY_UP, [this] { onDespause(); });

	std::cout << "\nEXIT PAUSE.\n";

	sdlutils().virtualTimer().resume();
}

void PauseMenuState::onDespause()
{
	std::cout << "last state in pause: " << GetLastState() << "\n";

	GameStateMachine::instance()->setState(GetLastState());
	//GameStateMachine::instance()->popState();
}
