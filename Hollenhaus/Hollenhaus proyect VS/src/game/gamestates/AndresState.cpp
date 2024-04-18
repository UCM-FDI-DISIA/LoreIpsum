#include "pch.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "AndresState.h"
#include "../components/HandComponent.h"
#include "../components/managers/DragManager.h"
#include "../factories/CardFactory_v1.h"
#include "../factories/BoardFactory_v0.h"

class CardFactory_v1;

AndresState::AndresState() :
	hand_()
{
	auto factory = new CardFactory_v1();
	auto boardFactory = new BoardFactory_v0(4);
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
		ecs::entity_t card = nullptr; //= factory->createCard(Vector2D(0, 0));
		card->setLayer(i + 1);
		hand_->getComponent<HandComponent>()->addCard(card);
	}
}

AndresState::~AndresState()
{
}

void AndresState::refresh()
{
	GameState::refresh();
}

void AndresState::update()
{
	GameState::update();
}

void AndresState::render() const
{
	GameState::render();
}
