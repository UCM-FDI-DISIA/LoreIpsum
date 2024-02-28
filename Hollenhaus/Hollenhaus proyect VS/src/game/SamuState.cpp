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
	auto board = boardFactory->createBoard();


	manager = Instantiate();
	manager->addComponent<MatchManager>();
	manager->getComponent<MatchManager>()->setBoard(board->getComponent<BoardManager>()->getBoard());

	factory->createHand();

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
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

	std::cout << manager->getComponent<MatchManager>()->getPlayer1Points() << std::endl;
}

void SamuState::render() const
{
	GameState::render();
}
