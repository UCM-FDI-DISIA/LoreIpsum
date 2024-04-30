#include <../pchs/pch.h>

#include "optionsMainMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/Button.h"
#include "../components/basics/Transform.h"

constexpr SDL_Color PEARL_HOLLENHAUS = { 226, 223, 210, 255 };

OptionsMainMenuState::OptionsMainMenuState()
{
}

OptionsMainMenuState::~OptionsMainMenuState()
{
}

void OptionsMainMenuState::refresh()
{
	GameState::refresh();
}

void OptionsMainMenuState::update()
{
	GameState::update();
}

void OptionsMainMenuState::render() const
{
	GameState::render();
}

void OptionsMainMenuState::onEnter()
{
	std::cout << "opciones " << std::endl;

	ecs::entity_t fondo = Instantiate(Vector2D(0, 0));
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(6, 6));
	fondo->setLayer(0);

	/*
	
	returnButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 170));
	returnButton->addComponent<TextComponent>("MENU PRINCIPAL", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	returnButton->addComponent<BoxCollider>();
	returnButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	returnButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	returnButton->addComponent<NPC>(0, 0);
	*/

	audioText = Instantiate(Vector2D(sdlutils().width() - 600, sdlutils().height() - 425));
	audioText->addComponent<TextComponent>("VOLUME", "8bit_size_32", PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	audioText->setLayer(1);

	fullScreenText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 300));
	fullScreenText->addComponent<TextComponent>("PANTALLA COMPLETA", "8bit_size_32", PEARL_HOLLENHAUS, 400, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	fullScreenText->addComponent<BoxCollider>();
	fullScreenText->getComponent<BoxCollider>()->setSize(Vector2D(400, 40));
	fullScreenText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-200, -20));
	
	windowModeText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 200));
	windowModeText->addComponent<TextComponent>("MODO VENTANA", "8bit_size_32", PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	windowModeText->addComponent<BoxCollider>();
	windowModeText->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	windowModeText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));

	returnButton = Instantiate(Vector2D(10, 10));
	returnButton->addComponent<Transform>();
	returnButton->addComponent<BoxCollider>();
	returnButton->addComponent<SpriteRenderer>("boton_flecha");
	//exitButton->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	returnButton->addComponent<Button>();
	returnButton->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(0); });
	
}

void OptionsMainMenuState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();
}
