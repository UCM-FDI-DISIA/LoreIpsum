#include "pch.h"
#include "MultiplayerGameState.h"

MultiplayerGameState::MultiplayerGameState()
{
	TuVieja("Loading MultiplayerGameState");
}

MultiplayerGameState::~MultiplayerGameState()
{
}

void MultiplayerGameState::refresh()
{
	GameState::refresh();
}

void MultiplayerGameState::update()
{
	GameState::update();
}

void MultiplayerGameState::render() const
{
	GameState::render();
}

void MultiplayerGameState::onEnter()
{
	TuVieja("ENTER MultiplayerGameState");

}

void MultiplayerGameState::onExit()
{
	TuVieja("EXIT MultiplayerGameState");

}
