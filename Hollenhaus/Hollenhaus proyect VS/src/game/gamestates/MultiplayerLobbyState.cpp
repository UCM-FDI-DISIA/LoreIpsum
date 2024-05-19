#include <../pchs/pch.h>
#include "MultiplayerLobbyState.h"
#include "../components/NPC.h"
#include "../components/InputForTextWritter.h"
#include "../components/TextWritter.h"
#include "../components/basics/TextComponent.h"
#include "../components/CopyTextComponentOnClipboardButton.h"
#include "../components/PasteOnTextComponentButton.h"
#include "../components/SendIPFromTextComponent.h"
#include "../components/SendInvitationButton.h"
#include "../components/multiplayer/NetLobby.h"
#include "../components/LobbyStatusIndicator.h"
#include "../components/GetIPv4.h"
#include "../components/ClickableText.h"
#include "../components/Clickable.h"


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

	// Imagen de fondo para el lobby
	ecs::entity_t lobbyBG = Instantiate(Vector2D(0, 0));
	lobbyBG->addComponent<SpriteRenderer>("multiplayer_lobby_bg");

	auto titulo = Instantiate(Vector2D());
	auto text = titulo->addComponent<TextComponent>(
		"SALA DE ESPERA", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 
		500, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center
	);
	titulo->getComponent<Transform>()->setGlobalPos(
		sdlutils().width()/2, 
		50
	);


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
	exit->addComponent<Clickable>("boton_flecha", true);

	// Entidad cuadro de texto para recoger una ip
	ecs::entity_t cuadroTexto = Instantiate(Vector2D(400, 300));
	cuadroTexto->addComponent<TextComponent>("", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	cuadroTexto->addComponent<TextWritter>();
	cuadroTexto->addComponent<InputForTextWritter>();

	// Botón para pegar el clipboard en el cuadro de texto
	ecs::entity_t pasteButton = Instantiate(Vector2D(400, 350));
	pasteButton->addComponent<TextComponent>("PEGAR", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	pasteButton->addComponent<BoxCollider>();
	pasteButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	pasteButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	pasteButton->addComponent<PasteOnTextComponentButton>(cuadroTexto->getComponent<TextComponent>());
	pasteButton->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	// Texto que guarda y muestra tu IP
	ecs::entity_t idHint = Instantiate(Vector2D());
	auto getipv4 = idHint->addComponent<GetIPv4>();
#if _DEBUG
	idHint->addComponent<TextComponent>("localhost", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
#else
	auto idHintText = idHint->addComponent<TextComponent>(getipv4->GetIP(), Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	idHint->getComponent<Transform>()->setGlobalPos(sdlutils().width() - idHintText->getTexture()->width() + 75, 50);
#endif // 

	// Botón para copiar tu IP al clipboard
	ecs::entity_t copyButton = Instantiate(Vector2D(700, 100));
	copyButton->addComponent<TextComponent>("COPIAR IP", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	copyButton->addComponent<BoxCollider>();
	copyButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	copyButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	copyButton->addComponent<CopyTextComponentOnClipboardButton>(idHint->getComponent<TextComponent>());
	copyButton->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);


	// Texto que renderiza el estado del lobby
	ecs::entity_t lobbyStatusRenderer = Instantiate(Vector2D(400, 400));
	lobbyStatusRenderer->addComponent<TextComponent>("", Fonts::GROTESK_16, Colors::PEARL_HOLLENHAUS, 500, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);


	// Para almacenar el estado del lobby
	ecs::entity_t lobbyStatus = Instantiate();
	lobbyStatus->addComponent<LobbyStatusIndicator>(lobbyStatusRenderer->getComponent<TextComponent>());


	// El NetLobby.
	// En DEBUG necesita pasarle el puerto, para no crear dos instancias en el mismo puerto.
	// En release se le asigna el puerto 2000 automáticamente
	ecs::entity_t netLobby = Instantiate();
#if _DEBUG
	int a;
	std::cin >> a;
	netLobby->addComponent<NetLobby>(static_cast<Uint16>(a), lobbyStatus->getComponent<LobbyStatusIndicator>());
#else
	netLobby->addComponent<NetLobby>(static_cast<Uint16>(2000), lobbyStatus->getComponent<LobbyStatusIndicator>());
#endif // 


	// Botón para enviar una invitación a aquella IP que esté guardada en el cuadro de texto
	ecs::entity_t sendInvButton = Instantiate(Vector2D(600, 530));
	sendInvButton->addComponent<TextComponent>("ENVIAR INVITACIÓN", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	sendInvButton->addComponent<BoxCollider>();
	sendInvButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	sendInvButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	sendInvButton->addComponent<SendIPFromTextComponent>(cuadroTexto->getComponent<TextComponent>(), netLobby->getComponent<NetLobby>());
	sendInvButton->addComponent<SendInvitationButton>();
	sendInvButton->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
}

void MultiplayerLobbyState::onExit()
{
	TuVieja("EXIT MultiplayerLobbyState");

	mngr().Free();
}
