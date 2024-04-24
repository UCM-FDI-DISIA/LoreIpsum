#include <../pchs/pch.h>

#include "optionsMainMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/Button.h"
#include "../components/basics/Transform.h"

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
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(2, 1));
	fondo->setLayer(0);

	/*
	
	returnButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 170));
	returnButton->addComponent<TextComponent>("MENU PRINCIPAL", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	returnButton->addComponent<BoxCollider>();
	returnButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	returnButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	returnButton->addComponent<NPC>(0, 0);
	*/

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
}
