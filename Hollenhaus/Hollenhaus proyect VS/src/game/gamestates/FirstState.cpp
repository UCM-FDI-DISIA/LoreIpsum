#include "..\pchs\pch.h"
#include "FirstState.h"

FirstState::FirstState()
{
}

FirstState::~FirstState()
{
}

void FirstState::update()
{
	GameState::update();
}

void FirstState::render() const
{
	GameState::render();
}

void FirstState::refresh()
{
	GameState::refresh();
}

void FirstState::onEnter()
{
	GameStateMachine::instance()->setState(GameStates::LOGOSTATE, true, true);
}

void FirstState::onExit()
{
}
