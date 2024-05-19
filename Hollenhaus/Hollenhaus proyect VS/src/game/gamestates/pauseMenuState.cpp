#include <../pchs/pch.h>

#include "pauseMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"
#include "game/components/Clickable.h"
#include "game/components/ClickableText.h"
#include "../components/basics/TextComponent.h"
#include "../components/Button.h"

PauseMenuState::PauseMenuState()
{
	TuVieja("Loading PauseMenuState");
}

PauseMenuState::~PauseMenuState() 
{

}

void PauseMenuState::update()
{
	GameState::update();
}

void PauseMenuState::render() const
{
	GameState::render();
}

void PauseMenuState::refresh()
{
	GameState::refresh();
}

void PauseMenuState::onEnter()
{
	std::cout << "\nENTER PAUSE.\n";

	//SetLastState(GameStates::PAUSEMENU);

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });

	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(100, 100);
	fondo->setLayer(0);

	//// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GetLastState()); // Lleva a la oficina (2).
	exit->setLayer(5);
	exit->addComponent<Clickable>("boton_flecha", true);

	auto font = "space_grotesk_bold_40";

	// mirar mazo
	mirarMazo = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 400));
	mirarMazo->addComponent<TextComponent>("MIRAR MAZO", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	mirarMazo->addComponent<BoxCollider>();
	mirarMazo->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	mirarMazo->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	mirarMazo->addComponent<NPC>(GameStates::MAZEMENU, 0);
	mirarMazo->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	// opciones
	options = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 360));
	options->addComponent<TextComponent>("OPCIONES", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	options->addComponent<BoxCollider>();
	options->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	options->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	options->addComponent<NPC>(GameStates::OPTIONSMENU, 0);
	options->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	// guardar
	guardar = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 320));
	guardar->addComponent<TextComponent>("GUARDAR", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	guardar->addComponent<BoxCollider>();
	guardar->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	guardar->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	guardar->addComponent<Button>();
	guardar->getComponent<Button>()->connectToButton([this] { saveData(); });
	guardar->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	// main menu
	mainmenu = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 280));
	mainmenu->addComponent<TextComponent>("VOLVER AL MENÚ", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 400, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	mainmenu->addComponent<BoxCollider>();
	mainmenu->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	mainmenu->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	mainmenu->addComponent<NPC>(GameStates::MAINMENU, 0);
	mainmenu->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	// salir
	salir = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 240));
	salir->addComponent<TextComponent>("SALIR", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	salir->addComponent<BoxCollider>();
	salir->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	salir->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	salir->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
	ih().insertFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { exitGame(); });

	sdlutils().virtualTimer().pause();
}

void PauseMenuState::onExit()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onDespause(); });

	GameStateMachine::instance()->getMngr()->Free();

	std::cout << "\nEXIT PAUSE.\n";

	sdlutils().virtualTimer().resume();
}

void PauseMenuState::onDespause()
{
	std::cout << "holaaaaa" << "\n";

	GameStateMachine::instance()->setState(GetLastState());
}

void PauseMenuState::exitGame()
{
	if (salir->getComponent<BoxCollider>()->isCursorOver())
	{
		sdlutils().closeWindow();
	}
}