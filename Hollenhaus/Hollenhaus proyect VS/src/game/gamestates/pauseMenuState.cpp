#include "pch.h"
#include "pauseMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../GameStateMachine.h"

PauseMenuState::PauseMenuState()
{
	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });
}

PauseMenuState::~PauseMenuState() 
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().PAUSEKEY_UP, [this] { onDespause(); });
}

void PauseMenuState::refresh() {}

void PauseMenuState::update() {}

void PauseMenuState::render() const {}

void PauseMenuState::onEnter()
{
	sdlutils().virtualTimer().pause();
}

void PauseMenuState::onExit()
{
	sdlutils().virtualTimer().resume();
}

void PauseMenuState::onDespause()
{
	GameStateMachine::instance()->setState(previousState);
}
