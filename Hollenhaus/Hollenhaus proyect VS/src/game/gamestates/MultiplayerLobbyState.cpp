#include "pch.h"
#include "MultiplayerLobbyState.h"
#include "../components/NPC.h"

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


	// --- Boton para volver al menu principal ---
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GameStates::MAINMENU); // Lleva al menu (0).
	exit->setLayer(2);
}

void MultiplayerLobbyState::onExit()
{
	TuVieja("EXIT MultiplayerLobbyState");
	mngr().Free();
}
