#include "pch.h"
#include "AndresState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "HandComponent.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

#include "BoardFactory_v0.h"

AndresState::AndresState() :
	hand_()
{
	CardFactory_v0* factory = new CardFactory_v0();
	BoardFactory_v0* boardFactory = new BoardFactory_v0(4);
	hand_ = Instantiate();
	hand_->addComponent<Transform>();
	hand_->addComponent<SpriteRenderer>("hand");
	hand_->addComponent<HandComponent>();
	hand_->setLayer(8);

	//cambiado por la boardFactory para que no de errores
	//factory->createBoard();

	boardFactory->createBoard();

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();

	for (int i = 0; i < 7; i++)
	{
		ecs::entity_t card = nullptr;//= factory->createCard(Vector2D(0, 0));
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