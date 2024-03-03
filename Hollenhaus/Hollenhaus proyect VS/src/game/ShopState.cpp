#include "ShopState.h"
#include "Manager.h"
#include "TextComponent.h"

ShopState::ShopState()
{
	std::cout << "\nLoading Shop";
}

void ShopState::update()
{
	GameState::update();
}

void ShopState::render() const  
{
	GameState::render();
}

void ShopState::refresh()
{
	GameState::refresh();
}

void ShopState::onEnter()
{
	ecs::entity_t pruebaTxt = Instantiate(Vector2D(400, 30));
	pruebaTxt->addComponent<TextComponent>("TIENDA", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	pruebaTxt->setLayer(1);



	std::cout << "\nEnter shop\n";
	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("tiendafondo");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);
	//------Botones
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

void ShopState::onExit() 
{
	std::cout << "\nExit shop\n";
	GameStateMachine::instance()->getMngr()->Free();
}
