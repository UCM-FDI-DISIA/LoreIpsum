#include "MainMenuState.h"
#include "Entity.h"
#include "Manager.h"
#include "NPC.h"

MainMenuState::MainMenuState()
	 
{
	
	std::cout << "\nLoading Menu";
}

void MainMenuState::update()
{
}

void MainMenuState::render() const 
{
}

void MainMenuState::refresh()
{
}

void MainMenuState::onEnter() 
{
	std::cout << "\nEnter menu\n";
	ecs::entity_t boton1 = Instantiate();
	boton1->addComponent<Transform>();
	boton1->addComponent<SpriteRenderer>("boton");
	boton1->addComponent<BoxCollider>();
	//boton1->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	boton1->getComponent<Transform>()->getGlobalPos().set(100, 200);
	boton1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	boton1->addComponent<NPC>(6);
	boton1->setLayer(1);

}

void MainMenuState::onExit() 
{
	std::cout << "\nExit menu\n";
}

