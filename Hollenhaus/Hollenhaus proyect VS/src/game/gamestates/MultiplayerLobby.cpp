#include "pch.h"
#include "MultiplayerLobby.h"

MultiplayerLobby::MultiplayerLobby()
{
	TuVieja("Loading MultiplayerLobbyState");
}

MultiplayerLobby::~MultiplayerLobby()
{
}

void MultiplayerLobby::refresh()
{
	GameState::refresh();
}

void MultiplayerLobby::update()
{
	GameState::update();
}

void MultiplayerLobby::render() const
{
	GameState::render();
}

void MultiplayerLobby::onEnter()
{
	TuVieja("ENTER MultiplayerLobbyState");

}

void MultiplayerLobby::onExit()
{
	TuVieja("EXIT MultiplayerLobbyState");

}
