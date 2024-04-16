#include "pch.h"
#include "MultiplayerPreGameState.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"

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

	// Imagen de fondo para el lobby
	ecs::entity_t pregameBG = Instantiate(Vector2D(0, 0));
	pregameBG->addComponent<SpriteRenderer>("multiplayer_pregame_bg");

}

void MultiplayerPreGameState::onExit()
{
	TuVieja("EXIT MultiplayerPreGameState");
	mngr().Free();

}

