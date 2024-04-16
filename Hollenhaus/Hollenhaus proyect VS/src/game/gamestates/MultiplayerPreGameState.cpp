#include "pch.h"
#include "MultiplayerPreGameState.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/Button.h"

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

	// Botón para setear tu mazo en Data
	ecs::entity_t setMazeButton = Instantiate(Vector2D(400, 300));
	setMazeButton->addComponent<TextComponent>("SET MAZE", "8bit_size_32", SDL_Color({ 0, 0, 0 ,0 }), 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	setMazeButton->addComponent<BoxCollider>();
	setMazeButton->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	setMazeButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	setMazeButton->addComponent<Button>();
	//setMazeButton->getComponent<Button>()->connectToButton([this] {AcceptConection(); });

	// Botón que prepara tu estado para comenzar la partida
	ecs::entity_t readyButton = Instantiate(Vector2D(650, 500));
	TextComponent* tc = readyButton->addComponent<TextComponent>("READY", "8bit_size_32", SDL_Color({ 255, 0, 0 ,0 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	readyButton->addComponent<BoxCollider>();
	readyButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	readyButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	readyButton->addComponent<Button>();
	readyButton->getComponent<Button>()->connectToButton([this, tc] {tc->setColor(SDL_Color({0, 255, 0 ,0})); });
}

void MultiplayerPreGameState::onExit()
{
	TuVieja("EXIT MultiplayerPreGameState");
	mngr().Free();

}

