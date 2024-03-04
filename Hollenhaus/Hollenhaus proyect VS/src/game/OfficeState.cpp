#include "OfficeState.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"
#include "TextComponent.h"

OfficeState::OfficeState()
{
	std::cout << "\nLoading OfficeState.";
}

void OfficeState::update()
{
	GameState::update();
}

void OfficeState::render() const
{
	GameState::render();
}

void OfficeState::refresh()
{
	GameState::refresh();
}

void OfficeState::onEnter()
{
	std::cout << "\nENTER OFFICE.\n";
	
	//------Texto de la oficina.
	ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	officeText->addComponent<TextComponent>("OFICINA", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	officeText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("oficinafondo");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

	//------Boton para volver:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	exit->setLayer(1);
}

void OfficeState::onExit()
{
	std::cout << "\nEXIT OFFICE.\n";
	GameStateMachine::instance()->getMngr()->Free();
}

