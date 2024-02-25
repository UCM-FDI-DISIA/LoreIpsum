#include "PaigroState.h"

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

	ecs::entity_t ent = Instantiate();
	ent->addComponent<Transform>();
	ent->addComponent<SpriteRenderer>("npc");
	ent->addComponent<BoxCollider>();
	ent->getComponent<Transform>()->getGlobalScale().set(0.4f, 0.4f);
	ent->getComponent<Transform>()->getGlobalPos().set(300, 200);
	ent->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	ent->addComponent<NPC>();


}

void PaigroState::onExit() const
{
	std::cout << "\nBUENAS NOCHES\n";
}