#include "checkML.h"
#include "pch.h"
#include "multiplayerModeState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"

constexpr SDL_Color ROJO_HOLLENHAUS = { 148, 47, 55, 255 };

MultiplayerModeState::MultiplayerModeState()
{
	
}

MultiplayerModeState::~MultiplayerModeState()
{
}

void MultiplayerModeState::refresh()
{
	GameState::refresh();
}

void MultiplayerModeState::update()
{
	GameState::update();
}

void MultiplayerModeState::render() const
{
	GameState::render();
}

void MultiplayerModeState::onEnter()
{
	std::cout << "multiplayer " << getMoney() << std::endl;

	ecs::entity_t fondo = Instantiate(Vector2D(0, 0));
	fondo->addComponent<SpriteRenderer>("mpfondo");
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(2, 2));
	fondo->setLayer(0);


	mainMenuButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 170));
	mainMenuButton->addComponent<TextComponent>("MENU PRINCIPAL", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	mainMenuButton->addComponent<BoxCollider>();
	mainMenuButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	mainMenuButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	mainMenuButton->addComponent<NPC>(0, 0);
	
	iniGameButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 120));
	iniGameButton->addComponent<TextComponent>("INICIAR", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	iniGameButton->addComponent<BoxCollider>();
	iniGameButton->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	iniGameButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-50, -20));
	iniGameButton->addComponent<NPC>(13, 0);


}

void MultiplayerModeState::onExit()
{
}

