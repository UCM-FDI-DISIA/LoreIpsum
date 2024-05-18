#include <../pchs/pch.h>
#include "EndGameState.h"


EndGameState::EndGameState()
{
}

EndGameState::~EndGameState()
{
}

void EndGameState::update()
{
	GameState::update();
}

void EndGameState::render() const
{
	GameState::render();
}

void EndGameState::refresh()
{
	GameState::refresh();
}

void EndGameState::onEnter()
{
	std::cout << "\nENTER ENDGAME.\n";
}

void EndGameState::onExit()
{
	std::cout << "\nEXIT ENDGAME.\n";
	GameStateMachine::instance()->getMngr()->Free();
}
