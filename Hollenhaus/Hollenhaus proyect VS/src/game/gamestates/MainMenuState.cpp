#include "pch.h"
#include "MainMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/NPC.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"


constexpr SDL_Color ROJO_HOLLENHAUS = { 148, 47, 55, 255 };

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
	std::cout << "\nENTER MENU.\n";

	/// Fondo
	//-----Ciudad de fondo:
	ecs::entity_t fondo = Instantiate(Vector2D(0,0));
	fondo->addComponent<SpriteRenderer>("main_menu_bg");
	fondo->getComponent<Transform>()->setGlobalScale(Vector2D(0.56,0.56));
	fondo->setLayer(0);


	//----------------------------------De momento el unico texto con interaccion es el que lleva a un nuevo juego.
	//------Textos del menu principal:
	//----Texto del titulo.
	//ecs::entity_t titleText = Instantiate(Vector2D(400, 50));
	//titleText->addComponent<TextComponent>("HÖLLENHAUS", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 450, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para un nuevo juego.
	newGameButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 120));
	newGameButton->addComponent<TextComponent>("NUEVA PARTIDA", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	newGameButton->addComponent<BoxCollider>();
	newGameButton->getComponent<BoxCollider>()->setSize(Vector2D(300,40));
	newGameButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	newGameButton->addComponent<NPC>(1, 0); // Esto es graciosisimo

	//----Texto para continuar partida.
	//ecs::entity_t continueText = Instantiate(Vector2D(400, 250));
	//continueText->addComponent<TextComponent>("CONTINUE", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para las opciones
	//ecs::entity_t optionsText = Instantiate(Vector2D(400, 300));
	//optionsText->addComponent<TextComponent>("OPTIONS", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para salir.
	exitButton = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() - 70));
	exitButton->addComponent<TextComponent>("SALIR", "8bit_size_32", ROJO_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setSize(Vector2D(100,32));
	exitButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(50, -16));
	ih().insertFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { exitGame(); });

	sdlutils().soundEffects().at("menutheme").play(-1);
	sdlutils().soundEffects().at("menutheme").setChannelVolume(10);
}

void MainMenuState::onExit() {
	std::cout << "\nEXIT MENU.\n";
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { exitGame(); });
	sdlutils().soundEffects().at("menutheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}

void MainMenuState::exitGame()
{
	if (exitButton->getComponent<BoxCollider>()->isCursorOver())
	{
		sdlutils().closeWindow();
	}
}

