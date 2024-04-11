#include "pch.h"
#include "MultiplayerLobbyState.h"
#include "../components/NPC.h"
#include "../components/InputForTextWritter.h"
#include "../components/TextWritter.h"
#include "../components/basics/TextComponent.h"
#include "../components/CopyTextComponentOnClipboardButton.h"
#include "../components/PasteOnTextComponentButton.h"


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

	// Entidad cuadro de texto para recoger una ip
	ecs::entity_t cuadroTexto = Instantiate(Vector2D(sdlutils().width()/2, sdlutils().height()/2));
	//cuadroTexto->addComponent<SpriteRenderer>("black_box");
	//cuadroTexto->addComponent<BoxCollider>()->setAnchoredToSprite(true);
	cuadroTexto->addComponent<TextComponent>("Introducir ip", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	cuadroTexto->addComponent<TextWritter>();
	cuadroTexto->addComponent<InputForTextWritter>();

	ecs::entity_t pasteButton = Instantiate(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2 + 100));
	pasteButton->addComponent<SpriteRenderer>("black_box");
	pasteButton->addComponent<BoxCollider>()->setAnchoredToSprite(true);
	pasteButton->addComponent<PasteOnTextComponentButton>(cuadroTexto->getComponent<TextComponent>());

	ecs::entity_t idHint = Instantiate(Vector2D(100, 100));
	idHint->addComponent<TextComponent>("brr", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 300, Text::BoxPivotPoint::LeftTop, Text::TextAlignment::Left);

	ecs::entity_t copyButton = Instantiate(Vector2D(400, 100));
	copyButton->addComponent<SpriteRenderer>("black_box");
	copyButton->addComponent<BoxCollider>()->setAnchoredToSprite(true);
	copyButton->addComponent<CopyTextComponentOnClipboardButton>(idHint->getComponent<TextComponent>());
}

void MultiplayerLobbyState::onExit()
{
	TuVieja("EXIT MultiplayerLobbyState");

	mngr().Free();
}
