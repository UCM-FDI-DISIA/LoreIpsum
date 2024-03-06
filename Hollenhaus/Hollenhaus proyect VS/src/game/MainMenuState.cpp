#include "MainMenuState.h"
#include "Entity.h"
#include "Manager.h"
#include "NPC.h"
#include "TextComponent.h"

constexpr SDL_Color ROJO_HOLLENHAUS = { 148, 47, 55, 255 };

MainMenuState::MainMenuState()
{
	
	std::cout << "\nLoading MainMenuState.";
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
	fondo->getComponent<Transform>()->setGlobalScale(0.5,0.5);
	fondo->setLayer(0);


	//----------------------------------De momento el unico texto con interaccion es el que lleva a un nuevo juego.
	//------Textos del menu principal:
	//----Texto del titulo.
	//ecs::entity_t titleText = Instantiate(Vector2D(400, 50));
	//titleText->addComponent<TextComponent>("HÖLLENHAUS", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 450, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para un nuevo juego.
	ecs::entity_t newGameText = Instantiate(Vector2D(sdlutils().width() - 150, sdlutils().height() - 100));
	newGameText->addComponent<TextComponent>("NUEVA PARTIDA", "8bit_32pt", ROJO_HOLLENHAUS, 300, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Right);
	newGameText->addComponent<BoxCollider>();
	newGameText->getComponent<BoxCollider>()->setSize(Vector2D(200,40));
	newGameText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	newGameText->addComponent<NPC>(1); // Esto es graciosisimo

	//----Texto para continuar partida.
	//ecs::entity_t continueText = Instantiate(Vector2D(400, 250));
	//continueText->addComponent<TextComponent>("CONTINUE", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para las opciones
	//ecs::entity_t optionsText = Instantiate(Vector2D(400, 300));
	//optionsText->addComponent<TextComponent>("OPTIONS", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	//----Texto para salir.
	ecs::entity_t exitText = Instantiate(Vector2D(sdlutils().width() - 100, sdlutils().height() - 50));
	exitText->addComponent<TextComponent>("SALIR", "8bit_32pt", ROJO_HOLLENHAUS, 50, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Right);

	sdlutils().soundEffects().at("menutheme").play(-1);
	sdlutils().soundEffects().at("menutheme").setChannelVolume(10);
}

void MainMenuState::onExit() {
	std::cout << "\nEXIT MENU.\n";
	sdlutils().soundEffects().at("menutheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}

