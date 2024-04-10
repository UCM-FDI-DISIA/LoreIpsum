#include "pch.h"
#include "MultiplayerPreGameState.h"


MultiplayerPreGameState::MultiplayerPreGameState()
{
	TuVieja("Loading MultiplayerPreGameState");
}

MultiplayerPreGameState::~MultiplayerPreGameState()
{
}

void MultiplayerPreGameState::refresh()
{
	GameState::refresh();
}

void MultiplayerPreGameState::update()
{
	GameState::update();
}

void MultiplayerPreGameState::render() const
{
	GameState::render();
}

void MultiplayerPreGameState::onEnter()
{
	TuVieja("ENTER MultiplayerPreGameState");

}

void MultiplayerPreGameState::onExit()
{
	TuVieja("EXIT MultiplayerPreGameState");

}

