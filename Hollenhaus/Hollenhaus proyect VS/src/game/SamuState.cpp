#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

#include "Factory.h"

#include "BoardFactory.h"

#include "../MatchManager.h"

#include "BoardManager.h"

SamuState::SamuState() : GameState() {


	CardFactory_v0* factory = new CardFactory_v0();

	BoardFactory* boardFactory = new BoardFactory(4, 4);
	board = boardFactory->createBoard();

	factory->createHand();

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();

	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.42, 0.56);

	background->addComponent<SpriteRenderer>("board");
	background->setLayer(-1);
}

SamuState::~SamuState()
{

}
//cleon: si está vacío se llama directamente al padre
void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	GameState::update();

	board->getComponent<BoardManager>()->updateScore();
	std::cout << board->getComponent<BoardManager>()->getPlayer1Points() << std::endl;
}

void SamuState::render() const
{
	GameState::render();
}
