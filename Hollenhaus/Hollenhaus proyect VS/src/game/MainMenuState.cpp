#include "MainMenuState.h"
#include "Entity.h"
#include "Manager.h"
#include "NPC.h"
#include "TextComponent.h"

MainMenuState::MainMenuState()
	 
{
	
	std::cout << "\nLoading Menu";
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
	std::cout << "\nEnter menu\n";

	//------Textos del menu principal:
	ecs::entity_t titleText = Instantiate(Vector2D(400, 50));
	titleText->addComponent<TextComponent>("HÖLLENHAUS", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 450, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	ecs::entity_t newGameText = Instantiate(Vector2D(400, 200));
	newGameText->addComponent<TextComponent>("NEW GAME", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	newGameText->addComponent<BoxCollider>();
	newGameText->getComponent<BoxCollider>()->setSize(Vector2D(200,40));
	newGameText->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	newGameText->addComponent<NPC>(1); // Lleva a la ciudad.

	ecs::entity_t continueText = Instantiate(Vector2D(400, 250));
	continueText->addComponent<TextComponent>("CONTINUE", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	
	ecs::entity_t optionsText = Instantiate(Vector2D(400, 300));
	optionsText->addComponent<TextComponent>("OPTIONS", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	ecs::entity_t exitText = Instantiate(Vector2D(400, 500));
	exitText->addComponent<TextComponent>("EXIT", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	
	//ecs::entity_t boton1 = Instantiate();
	//boton1->addComponent<Transform>();
	//boton1->addComponent<SpriteRenderer>("boton");
	//boton1->addComponent<BoxCollider>();
	////boton1->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	//boton1->getComponent<Transform>()->getGlobalPos().set(100, 200);
	//boton1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	//boton1->addComponent<NPC>(6);
	//boton1->setLayer(1);

}

void MainMenuState::onExit() 
{
	std::cout << "\nExit menu\n";
	GameStateMachine::instance()->getMngr()->Free();
}

