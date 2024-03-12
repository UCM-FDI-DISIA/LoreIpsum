#include "pch.h"
#include "PaigroState.h"
#include "../components/managers/Manager.h"

PaigroState::PaigroState() {
	TuVieja("Loading unos buenos BUENOS DIAS");
}
void PaigroState::update()
{
	GameState::update();
}

void PaigroState::render() const
{
	GameState::render();
}

void PaigroState::refresh()
{
	GameState::refresh();
}

void PaigroState::onEnter()
{
	std::cout << "\nBUENOS DIAS";

	/*ecs::entity_t boton1 = Instantiate();
	boton1->addComponent<Transform>();
	boton1->addComponent<SpriteRenderer>("boton_flecha");
	boton1->addComponent<BoxCollider>();
	boton1->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	boton1->getComponent<Transform>()->getGlobalPos().set(100, 200);
	boton1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	boton1->addComponent<NPC>(0);
	boton1->setLayer(1);*/
}

void PaigroState::onExit() 
{
	std::cout << "\nBUENAS NOCHES";
}