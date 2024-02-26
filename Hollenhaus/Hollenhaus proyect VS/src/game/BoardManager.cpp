#include "BoardManager.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "DropDetector.h"
#include "CellManager.h"

BoardManager::BoardManager() :
	cardsOnBoard(0)
{
}

BoardManager::~BoardManager()
{
}

void BoardManager::initComponent()
{
	// Seteamos el board al tamanio deseado
	_board.resize(WIDTH);
	for (int i = 0; i < WIDTH; i++) {
		_board[i].resize(HEIGTH);
	}

	// Cada elemento de la matriz tiene un nuevo Cell (entidad) vacío
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGTH; j++) {
			_board[i][j] = Instantiate(Vector2D(200 + i*100, 100 + j*100), ecs::grp::DROPS);
			auto cellCmp = _board[i][j]->addComponent<CellManager>();
			_board[i][j]->addComponent<BoxCollider>();


			_board[i][j]->addComponent<DropDetector>()->getCardPos().set(Vector2D(200 + i * 100, 100 + j * 100));


			_board[i][j]->getComponent<BoxCollider>()->setSize(
				Vector2D(sdlutils().images().at("card").width() * 0.25,
					(sdlutils().images().at("card").height()) * 0.25));
			cellCmp->setPosOnBoard(i, j);
		}
	}
	// Esto hay que sustituirlo por una factoría
}

void BoardManager::update()
{
}

bool BoardManager::AddCard(ecs::entity_t card, int posX, int posY)
{
	ecs::entity_t cell = _board[posX][posY];

	auto cellCmp = mngr().getComponent<CellManager>(cell);

	bool cardAdded = cellCmp->SetCard(card);

	if (cardAdded) {
		cardsOnBoard++;
	}

	return cardAdded;
}

bool BoardManager::IsFull()
{
	return cardsOnBoard == WIDTH * HEIGTH; // recordad que os mataré
}
