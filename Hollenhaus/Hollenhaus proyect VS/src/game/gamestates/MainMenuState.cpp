#include <../pchs/pch.h>

#include "MainMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/NPC.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"
#include "game/components/ClickableText.h"
#include "../SoundManager.h"


constexpr SDL_Color ROJO_HOLLENHAUS = { 148, 47, 55, 255 };
constexpr SDL_Color MIDNIGHT_HOLLENHAUS = { 16, 23, 32, 255 }; // texto color normal
constexpr SDL_Color MIDNIGHT_CLICK = { 49, 50, 78, 255 }; // click texto color
constexpr SDL_Color MIDNIGHT_HOVER = { 73, 21, 31, 255 }; // hover texto color
constexpr int VERTICAL_OFFSET = 150;


MainMenuState::MainMenuState()
{
	
	TuVieja("Loading MainMenuState");
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::render() const
{
	GameState::render();
}

void MainMenuState::refresh()
{
	GameState::refresh();
}

void MainMenuState::onEnter() 
{
	_Tu_Vieja("\nENTER MENU.\n");

	_Tu_Vieja("DINERO: " << getMoney());

	SetLastState(GameStates::MAINMENU);

	/// Fondo
	//-----Ciudad de fondo:
	ecs::entity_t fondo = Instantiate(Vector2D(0,0));
	fondo->addComponent<SpriteRenderer>("main_menu_bg");
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(0.356,0.356));
	fondo->setLayer(0);

	//----Texto para un nuevo juego.
	newGameButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 220 - VERTICAL_OFFSET));
	newGameButton->addComponent<TextComponent>("MODO HISTORIA", "space_grotesk_bold_32", MIDNIGHT_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	newGameButton->addComponent<BoxCollider>();
	newGameButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	newGameButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	newGameButton->addComponent<NPC>(GameStates::STORYMODEMENU, NPC::Type::BUTTON, "", 0, true, true); // Esto es graciosisimo
	newGameButton->addComponent<ClickableText>(MIDNIGHT_HOLLENHAUS, MIDNIGHT_CLICK, MIDNIGHT_HOVER);

	multiplayerButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 170 - VERTICAL_OFFSET));
	multiplayerButton->addComponent<TextComponent>("MULTIPLAYER", "space_grotesk_bold_32", MIDNIGHT_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	// multiplayerButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 170));
	multiplayerButton->addComponent<BoxCollider>();
	multiplayerButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	multiplayerButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	multiplayerButton->addComponent<NPC>(GameStates::MULTIPLAYER_LOBBY, 0);
	multiplayerButton->addComponent<ClickableText>(MIDNIGHT_HOLLENHAUS, MIDNIGHT_CLICK, MIDNIGHT_HOVER);

	optionsButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 120 - VERTICAL_OFFSET));
	optionsButton->addComponent<TextComponent>("OPCIONES", "space_grotesk_bold_32", MIDNIGHT_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	// optionsButton = Instantiate(Vector2D(sdlutils().width() - 148, sdlutils().height() - 120));
	optionsButton->addComponent<BoxCollider>();
	optionsButton->getComponent<BoxCollider>()->setSize(Vector2D(190, 40));
	optionsButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-40, -20));
	optionsButton->addComponent<NPC>(GameStates::OPTIONSMENU, 0);
	optionsButton->addComponent<ClickableText>(MIDNIGHT_HOLLENHAUS, MIDNIGHT_CLICK, MIDNIGHT_HOVER);

	exitButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 70 - VERTICAL_OFFSET));
	exitButton->addComponent<TextComponent>("SALIR", "space_grotesk_bold_32", MIDNIGHT_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setSize(Vector2D(100, 32));
	exitButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(50, -16));
	exitButton->addComponent<ClickableText>(MIDNIGHT_HOLLENHAUS, MIDNIGHT_CLICK, MIDNIGHT_HOVER);
	ih().insertFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { exitGame(); });

	/// MUSICA
	auto music = SoundManager::instance();
	music->startMusic(Sounds::MAIN_MENU_M);
}

void MainMenuState::onExit() {
	std::cout << "\nEXIT MENU.\n";

	Vector2D globalPos(-380.0f, 0);
	setLastPaulPos(globalPos);

	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { exitGame(); });

	auto music = SoundManager::instance();
	music->stopMusic(Sounds::MAIN_MENU_M);

	GameStateMachine::instance()->getMngr()->Free();
}

void MainMenuState::exitGame()
{
	if (exitButton->getComponent<BoxCollider>()->isCursorOver())
	{
		sdlutils().closeWindow();
	}
}

