#include <../pchs/pch.h>

#include "optionsMainMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/Button.h"
#include "../components/basics/Transform.h"
#include "game/components/Clickable.h"
#include "game/components/ClickableText.h"


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

	audioText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 420));
	audioText->addComponent<TextComponent>("VOLUMEN", "space_grotesk_bold_32", PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	audioText->setLayer(1);

	audioText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 360));
	audioText->addComponent<TextComponent>("PONER AQU� LA BARRA", "space_grotesk_bold_32", PEARL_HOLLENHAUS, 500, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	audioText->setLayer(1);

	//SONIDO (MIRAR MAS TARDE CON INES)
	//auto& sdl = *SDLUtils::instance();
	//sdl.soundEffects().at("citytheme").play(-1);
	//sdl.soundEffects().at("citytheme").setChannelVolume(10);

	fullScreenText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 300));
	fullScreenText->addComponent<TextComponent>("PANTALLA COMPLETA", "space_grotesk_bold_32", PEARL_HOLLENHAUS, 400, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	fullScreenText->addComponent<BoxCollider>();
	fullScreenText->getComponent<BoxCollider>()->setSize(Vector2D(400, 40));
	fullScreenText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-200, -20));
	fullScreenText->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	
	windowModeText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 240));
	windowModeText->addComponent<TextComponent>("MODO VENTANA", "space_grotesk_bold_32", PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	windowModeText->addComponent<BoxCollider>();
	windowModeText->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	windowModeText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	windowModeText->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	returnButton = Instantiate(Vector2D(10, 10));
	returnButton->addComponent<Transform>();
	returnButton->addComponent<BoxCollider>();
	returnButton->addComponent<SpriteRenderer>("boton_flecha");
	returnButton->addComponent<Button>();
	returnButton->getComponent<Button>()->connectToButton([this] { if((GetLastState() != GameStates::CITY) || (GetLastState() != GameStates::TUTORIAL_CITY)) { GameStateMachine::instance()->setState(GetLastState()); } else { GameStateMachine::instance()->setState(GameStates::PAUSEMENU); }});
	returnButton->addComponent<Clickable>("boton_flecha", true);
}

void OptionsMainMenuState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();
}
