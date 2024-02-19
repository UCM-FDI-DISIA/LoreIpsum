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
			_board[i][j] = GameStateMachine::instance()->getMngr()->addEntity();
			GameStateMachine::instance()->getMngr()->addComponent<CellManager>(_board[i][j]);
		}
	}
	// Esto hay que sustituirlo por una factoría
}

void BoardManager::update()
{
}

void BoardManager::AddCard(ecs::entity_t card, int posX, int posY)
{
	ecs::entity_t cell = _board[posX][posY];
	GameStateMachine::instance()->getMngr()->getComponent<CellManager>(cell)->SetCard(card);

	
	
}
