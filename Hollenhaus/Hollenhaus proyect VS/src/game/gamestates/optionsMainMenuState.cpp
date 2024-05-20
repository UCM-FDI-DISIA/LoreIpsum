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
#include "../SoundManager.h"


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

	music = SoundManager::instance();

	music->startMusic(Sounds::MUSIC::OFFICE_M);

	ecs::entity_t fondo = Instantiate(Vector2D(0, 0));
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(6, 6));
	fondo->setLayer(0);

	audioText = Instantiate(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() - 420));
	audioText->addComponent<TextComponent>("VOLUMEN", Fonts::GROTESK_32, PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	audioText->setLayer(1);

	audioText = Instantiate(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() - 360));
	audioText->addComponent<TextComponent>(std::to_string(music->getVolume()), Fonts::GROTESK_32, PEARL_HOLLENHAUS, 500, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	audioText->setLayer(1);

	/*windowModeText->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	windowModeText->addComponent<Button>()->connectToButton([this]
		{
			sdlutils().setWindowed();
		});*/

	ecs::entity_t audioUP = Instantiate();
	audioUP->addComponent<Transform>();
	audioUP->addComponent<SpriteRenderer>("UpDrawer");
	audioUP->addComponent<BoxCollider>();
	audioUP->addComponent<Clickable>("UpDrawer", true);
	audioUP->getComponent<Transform>()->setGlobalAngle(90.0f);
	audioUP->getComponent<Transform>()->setGlobalPos(sdlutils().width() / 2 + 50, sdlutils().height() - 400);
	//audioUP->getComponent<Transform>()->setRelativePos(sdlutils().width(), sdlutils().height());
	//audioUP->getComponent<Transform>()->setGlobalScale(botScale);
	audioUP->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	audioUP->addComponent<Button>();
	audioUP->getComponent<Button>()->connectToButton([this]() { 
		music->addVolume(10);
		audioText->getComponent<TextComponent>()->setTxt(std::to_string(music->getVolume()));
		});
	audioUP->setLayer(2);

	ecs::entity_t audioDOWN = Instantiate();
	audioDOWN->addComponent<Transform>();
	audioDOWN->addComponent<SpriteRenderer>("DownDrawer");
	audioDOWN->addComponent<BoxCollider>();
	audioDOWN->addComponent<Clickable>("DownDrawer", true);
	audioDOWN->getComponent<Transform>()->setGlobalAngle(90.0f);
	audioDOWN->getComponent<Transform>()->setGlobalPos(sdlutils().width() / 2.0f - audioDOWN->getComponent<SpriteRenderer>()->getImageSize().getX() - 50.0f, sdlutils().height() - 400);
	audioDOWN->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	audioDOWN->addComponent<Button>();
	audioDOWN->getComponent<Button>()->connectToButton([this]() {
		music->addVolume(-10);
		audioText->getComponent<TextComponent>()->setTxt(std::to_string(music->getVolume()));

		});
	audioDOWN->setLayer(2);



	fullScreenText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 300));
	fullScreenText->addComponent<TextComponent>("PANTALLA COMPLETA", Fonts::GROTESK_32, PEARL_HOLLENHAUS, 400, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	fullScreenText->addComponent<BoxCollider>();
	fullScreenText->getComponent<BoxCollider>()->setSize(Vector2D(400, 40));
	fullScreenText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-200, -20));
	fullScreenText->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	fullScreenText->addComponent<Button>()->connectToButton([this]
	{
		sdlutils().setFullscreen();
	});
	
	windowModeText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 240));
	windowModeText->addComponent<TextComponent>("MODO VENTANA", Fonts::GROTESK_32, PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	windowModeText->addComponent<BoxCollider>();
	windowModeText->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	windowModeText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	windowModeText->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	windowModeText->addComponent<Button>()->connectToButton([this]
	{
		sdlutils().setWindowed();
	});
	
	returnButton = Instantiate(Vector2D(10, 10));
	returnButton->addComponent<Transform>()->setGlobalPos(10,10);
	returnButton->addComponent<BoxCollider>();
	returnButton->addComponent<SpriteRenderer>("boton_flecha");
	returnButton->addComponent<Button>();
	returnButton->getComponent<Button>()->connectToButton([this] { if(GetLastState() == GameStates::MAINMENU) { GameStateMachine::instance()->setState(GameStates::MAINMENU); } else { GameStateMachine::instance()->setState(GameStates::PAUSEMENU); }});
	returnButton->addComponent<Clickable>("boton_flecha", true);
}

void OptionsMainMenuState::onExit()
{
	music->stopMusic(Sounds::MUSIC::OFFICE_M);


	GameStateMachine::instance()->getMngr()->Free();
}
