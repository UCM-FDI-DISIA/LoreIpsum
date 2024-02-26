#include "BoardManager.h"
#include "CellManager.h"
#include "GameStateMachine.h"
#include "Manager.h"
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
			_board[i][j] = mngr().addEntity();
			auto cellCmp = mngr().addComponent<CellManager>(_board[i][j]);
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
