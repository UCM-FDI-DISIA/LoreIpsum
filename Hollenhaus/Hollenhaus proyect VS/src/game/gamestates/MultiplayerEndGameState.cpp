#include "pch.h"
#include "MultiplayerEndGameState.h"

MultiplayerEndGameState::MultiplayerEndGameState()
{
	TuVieja("Loading MultiplayerEndGameState");
}

MultiplayerEndGameState::~MultiplayerEndGameState()
{
}

void MultiplayerEndGameState::refresh()
{
	GameState::refresh();
}

void MultiplayerEndGameState::update()
{
	GameState::update();
}

void MultiplayerEndGameState::render() const
{
	GameState::render();
}

void MultiplayerEndGameState::onEnter()
{
	TuVieja("ENTER MultiplayerEndGameState");

}

void MultiplayerEndGameState::onExit()
{
	TuVieja("EXIT MultiplayerEndGameState");
	mngr().Free();

}
