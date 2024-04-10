#include "pch.h"
#include "MultiplayerLobbyState.h"

MultiplayerLobbyState::MultiplayerLobbyState()
{
	TuVieja("Loading MultiplayerLobbyState");
}

MultiplayerLobbyState::~MultiplayerLobbyState()
{
}

void MultiplayerLobbyState::refresh()
{
	GameState::refresh();
}

void MultiplayerLobbyState::update()
{
	GameState::update();
}

void MultiplayerLobbyState::render() const
{
	GameState::render();
}

void MultiplayerLobbyState::onEnter()
{
	TuVieja("ENTER MultiplayerLobbyState");

}

void MultiplayerLobbyState::onExit()
{
	TuVieja("EXIT MultiplayerLobbyState");

}
