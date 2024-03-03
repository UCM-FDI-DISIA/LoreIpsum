#include "OfficeState.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"
#include "TextComponent.h"

OfficeState::OfficeState()
{
	std::cout << "\nLoading Office";
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
	std::cout << "\nEntering office\n";

	ecs::entity_t pruebaTxt = Instantiate(Vector2D(210, 30));
	pruebaTxt->addComponent<TextComponent>("OFICINA", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	pruebaTxt->setLayer(2);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("oficinafondo");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	//------Botones
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
}

void OfficeState::onExit()
{
	std::cout << "\nExit office\n";
	GameStateMachine::instance()->getMngr()->Free();
}

