#include <../pchs/pch.h>

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
	TuVieja("Loading PauseMenuState");
}

PauseMenuState::~PauseMenuState() 
{

}

void PauseMenuState::update()
{
	GameState::update();
}

void PauseMenuState::render() const
{
	GameState::render();
}

void PauseMenuState::refresh()
{
	GameState::refresh();
}

void PauseMenuState::onEnter()
{
	std::cout << "\nENTER PAUSE.\n";

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });

	//// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GetLastState());
	exit->setLayer(5);

	//// ---- CheckMaze:
	ecs::entity_t maze = Instantiate();
	maze->addComponent<Transform>();
	maze->addComponent<SpriteRenderer>("rice");
	maze->addComponent<BoxCollider>();
	Vector2D mazePos(120, 200);
	maze->getComponent<Transform>()->setGlobalPos(mazePos);
	maze->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	maze->addComponent<NPC>(18);
	maze->setLayer(5);

	sdlutils().virtualTimer().pause();
}

void PauseMenuState::onExit()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });

	GameStateMachine::instance()->getMngr()->Free();

	std::cout << "\nEXIT PAUSE.\n";

	sdlutils().virtualTimer().resume();
}

void PauseMenuState::onDespause()
{
	std::cout << "holaaaaa" << "\n";

	GameStateMachine::instance()->setState(GetLastState());
}
