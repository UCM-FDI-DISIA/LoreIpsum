#include "PaigroState.h"
#include "Manager.h"

PaigroState::PaigroState() {
	std::cout << "\nLoading unos buenos BUENOS DIAS\n";

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

void PaigroState::onEnter() const
{
	std::cout << "\nBUENOS DIAS\n";

	ecs::entity_t boton1 = Instantiate();
	boton1->addComponent<Transform>();
	boton1->addComponent<SpriteRenderer>("boton");
	boton1->addComponent<BoxCollider>();
	boton1->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	boton1->getComponent<Transform>()->getGlobalPos().set(100, 200);
	boton1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	boton1->addComponent<NPC>();

	ecs::entity_t boton2 = Instantiate();
	boton2->addComponent<Transform>();
	boton2->addComponent<SpriteRenderer>("boton");
	boton2->addComponent<BoxCollider>();
	boton2->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	boton2->getComponent<Transform>()->getGlobalPos().set(500, 200);
	boton2->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	boton2->addComponent<NPC>();


}

void PaigroState::onExit() const
{
	std::cout << "\nBUENAS NOCHES\n";
}