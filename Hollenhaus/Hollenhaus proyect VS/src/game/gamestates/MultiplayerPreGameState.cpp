#include <../pchs/pch.h>
#include "MultiplayerPreGameState.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/Button.h"
#include "../components/multiplayer/NetPregame.h"
#include "game/components/ClickableText.h"

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

	auto titulo = Instantiate(Vector2D());
	auto text = titulo->addComponent<TextComponent>(
		"¡PREPÁRATE!", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 
		600, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center
	);
	titulo->getComponent<Transform>()->setGlobalPos(
		sdlutils().width()/2, 
		50
	);

	// Botón para setear tu mazo en Data
	ecs::entity_t setMazeButton = Instantiate(Vector2D(400, 300));
	setMazeButton->addComponent<TextComponent>("ELEGIR MAZO", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	setMazeButton->addComponent<BoxCollider>();
	setMazeButton->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	setMazeButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	setMazeButton->addComponent<Button>();
	setMazeButton->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	//setMazeButton->getComponent<Button>()->connectToButton([this] {AcceptConection(); });


	// Botón que prepara tu estado para comenzar la partida
	ecs::entity_t readyButton = Instantiate(Vector2D(650, 500));
	TextComponent* tc = readyButton->addComponent<TextComponent>("READY", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	readyButton->addComponent<BoxCollider>();
	readyButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	readyButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	readyButton->addComponent<Button>();


	// el pregame y tal
	ecs::entity_t pregameEntity = Instantiate(Vector2D(400, 400));
	pregameEntity->addComponent<TextComponent>("OponentNotReady", Fonts::GROTESK_16, Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	NetPregame* netPregame = pregameEntity->addComponent<NetPregame>(pregameEntity->getComponent<TextComponent>(), tc);


	readyButton->getComponent<Button>()->connectToButton([this, netPregame] {netPregame->SetPlayerReady(!netPregame->GetPlayerReady()); });
}




void MultiplayerPreGameState::onExit()
{
	TuVieja("EXIT MultiplayerPreGameState");
	mngr().Free();

}

