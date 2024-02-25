#include "AndresState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "HandComponent.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

AndresState::AndresState() :
	hand_(Instantiate())
{
	CardFactory_v0* factory = new CardFactory_v0();
	hand_->addComponent<Transform>();
	hand_->addComponent<SpriteRenderer>("hand");
	hand_->addComponent<HandComponent>();
	hand_->setLayer(8);

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();

	for (int i = 0; i < 7; i++)
	{
		ecs::entity_t card = factory->createCard(Vector2D(400 + (i * 10), 400));
		card->setLayer(i + 1);
		hand_->getComponent<HandComponent>()->addCard(card);
	}
}

AndresState::~AndresState() {

}

void AndresState::refresh() {
	GameState::refresh();
}

void AndresState::update() {
	GameState::update();
}

void AndresState::render() const {
	GameState::render();
}