#include "pch.h"
#include "BoardManager.h"
#include "../../GameStateMachine.h"
#include "Manager.h"
#include "../basics/Transform.h"
#include "../basics/SpriteRenderer.h"
#include "../basics/BoxCollider.h"
#include "../DropDetector.h"
#include "../basics/TextComponent.h"
#include "../Cell.h"
#include "MatchManager.h"

//#include "IA_manager.h"


BoardManager::BoardManager()
{
	//BUENOS DIAS :) QUE BONITO CONYO
}

BoardManager::BoardManager(int size) : size(size)
{
}

BoardManager::~BoardManager()
{
}

void BoardManager::initComponent()
{

}

void BoardManager::update()
{
	
}

bool BoardManager::isFull() const
{
	return cardsOnBoard == size * size; // recordad que os matare
}


Cell* BoardManager::getCell(int x, int y) const
{
	return _board[x][y]->getComponent<Cell>();
}


std::list<SDLEventCallback> BoardManager::getEffects(Cell* cell) const
{
	return cell->getEffects();
}

bool BoardManager::setCard(int x, int y, Card* c, Players::Owner o)
{
	const auto cell = _board[x][y]->getComponent<Cell>();
	if (cell->getCard() != nullptr)
		return false;

	/// comunicacion bidireccional celda-carta
	cell->setCard(c, o);
	c->setCell(cell);

	/// anyade callback a la celda
	for (const auto& e : c->getEffects())
		cell->addEffect(e);

	//Cambia el color de la carta si es del jugador 2
	if (o == Players::PLAYER2) 
		c->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(104, 52, 177, 200);


	auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();
	//Gasta los puntos de accion correspondientes
	matchManager->substractActualPlayerActionPoints(c->getCost());

	// aumenta el contador al aniadir carta al tablero
	cardsOnBoard++;

	/// reaplica todos los efectos
	applyAllEffects();
	//matchManager->updateVisuals();
	updateScore();
	return true;
}

void BoardManager::updateScore()
{
	// Reinicia los valores
	pPlayer1 = 0;
	pPlayer2 = 0;

	//VA AL BOARD MANAGER
	// hace recuento de valores
	for (int j = 0; j < _board.size(); j++)
	{
		for (int i = 0; i < _board[j].size(); i++)
		{
			//si es del jugador 1
			if (_board[i][j]->getComponent<Cell>()->getOwner() == Players::PLAYER1)
				pPlayer1 += _board[i][j]->getComponent<Cell>()->getTotalValue();
			//si es el jugador 2 (normalmente npc)
			else if (_board[i][j]->getComponent<Cell>()->getOwner() == Players::IA)
				pPlayer2 += _board[i][j]->getComponent<Cell>()->getTotalValue();
		}
	}

	updateVisuals();
}

void BoardManager::applyAllEffects() const
{
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			if (_board[i][j]->getComponent<Cell>()->getCard() != nullptr)
				_board[i][j]->getComponent<Cell>()->setTotalValue(0);

	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			if (_board[i][j]->getComponent<Cell>()->getCard() != nullptr)
				_board[i][j]->getComponent<Cell>()->applyValue(_board[i][j]->getComponent<Cell>()->getCard());
}

void BoardManager::updateVisuals()
{
	//Cambia directamente el número, si queremos poner algún efecto cero que sería aquí
	scoreVisualJ1->getComponent<TextComponent>()->setTxt(std::to_string(pPlayer1));
	scoreVisualJ2->getComponent<TextComponent>()->setTxt(std::to_string(pPlayer2));
}


//falta refacorizar esto dividiendolo en metodos y teniendo en cuenta los metodos originales
int BoardManager::heuristicIA(IA_manager::State* s)
{
	//limpieza del tablero(card a null y reset de los efectos)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			_boardIA[i][j]->cleanEffectList();
			_boardIA[i][j]->setCard(nullptr, Players::NONE);
			_boardIA[i][j]->setTotalValue(0);
		}
	}


	Card* card = nullptr;
	Cell* cell = nullptr;

	//colocar todas las cartas en el tablero
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			if (s->_boardBools[i][j]) {//si hay una carta
				cell = _boardIA[i][j];
				card = s->_boardCards[i][j];

				cell->setCard(card,s->_boardOwners[i][j]);
				card->setCell(cell);

				/// anade callback a la celda
				for (const auto& e : card->getEffects())
					cell->addEffect(e);
			}
		}
	}


	//APPLY EFFECTS
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			if (_boardIA[i][j]->getCard() != nullptr) 
				_boardIA[i][j]->setTotalValue(0);
			
	
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			if (_boardIA[i][j]->getCard() != nullptr)
				_boardIA[i][j]->applyValue(_boardIA[i][j]->getCard());


	//UPDATE SCORE
	
	// Reinicia los valores
	int puntosPlayer1 = 0;
	int puntosPlayer2 = 0;

	//VA AL BOARD MANAGER
	// hace recuento de valores
	for (int j = 0; j < _boardIA.size(); j++)
	{
		for (int i = 0; i < _boardIA[j].size(); i++)
		{
			//si es del jugador 1
			if (_boardIA[i][j]->getOwner() == Players::PLAYER1)
				puntosPlayer1 += _boardIA[i][j]->getTotalValue();
			//si es el jugador 2 (normalmente npc)
			else if (_boardIA[i][j]->getOwner() == Players::PLAYER2)
				puntosPlayer2 += _boardIA[i][j]->getTotalValue();
		}
	}

	return puntosPlayer1-puntosPlayer2;
}

//inicializa el tablero de la IA
void BoardManager::initBoardIA()
{
	//creacion del tablero
	_boardIA.resize(size);

	for (int i = 0; i < size; i++) {
		_boardIA[i].resize(size);

		for (int j = 0; j < size; j++) {
			_boardIA[i][j] = new Cell();
		}
	}

	/// Inicializacion de referencias de cada celda
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			Cell* cell = _boardIA[i][j];

			/// CENTRO:
			///		SIZE PAR: n/2 && n/2 - 1
			///		SIZE IMPAR: floor(n/2)
			if (size % 2 == 0) // es un tablero par
			{
				// esta en ambos ejes en el centro (2x2 casillas posibles)
				if ((j == size / 2 || j == size / 2 - 1)
					&& (i == size / 2 || i == size / 2 - 1))
					cell->setCenter(true);
			}
			else // es un tablero impar
			{
				// esta en ambos ejes en el centro (1 unica casilla posible)
				// como ambos son ints, la division devuelve el entero redondeando hacia abajo siempre!
				if (j == size / 2 && i == size / 2)
					cell->setCenter(true);
			}

			/// ESQUINA:
			int n = size - 1;
			if (   (j == 0 && i == 0) // 0,0
				|| (j == 0 && i == n) // 0,n
				|| (j == n && i == n) // n,n
				|| (j == n && i == 0)) // n,0
				cell->setCorner(true);

			/// ADYACENTES:
			std::array<Cell*, ADJACENTS> adj;
			// inicializa a nullptr
			for (int m = 0; m < ADJACENTS; m++)
				adj[m] = nullptr;

			if (j > 0) adj[Effects::Up] = _boardIA[i][j - 1];
			if (i < n) adj[Effects::Right] = _boardIA[i + 1][j];
			if (j < n) adj[Effects::Down] = _boardIA[i][j + 1];
			if (i > 0) adj[Effects::Left] = _boardIA[i - 1][j];

			cell->setAdjacents(adj);
		}
	}
}

std::vector<std::vector<bool>> BoardManager::getBoardBoolsIA()
{ 
	std::vector<std::vector<bool>> board;

	//creacion del board
	board.resize(size);
	for (int i = 0; i < size; i++) {
		board[i].resize(size);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = _board[i][j]->getComponent<Cell>()->getCard() != nullptr;
		}
	}

	return board;
}

std::vector<std::vector<Card*>> BoardManager::getBoardCardsIA()
{
	std::vector<std::vector<Card*>> board;

	//creacion del board
	board.resize(size);
	for (int i = 0; i < size; i++) {
		board[i].resize(size);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = _board[i][j]->getComponent<Cell>()->getCard();
		}
	}

	return board;
}

std::vector<std::vector<Players::Owner>> BoardManager::getBoardOwnerIA()
{
	std::vector<std::vector<Players::Owner>> board;

	//creacion del board
	board.resize(size);
	for (int i = 0; i < size; i++) {
		board[i].resize(size);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = _board[i][j]->getComponent<Cell>()->getOwner();
		}
	}

	return board;
}

void BoardManager::initBoard()
{
	/// Inicializacion de referencias de cada celda
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			Cell* cell = _board[i][j]->getComponent<Cell>();

			/// CENTRO:
			///		SIZE PAR: n/2 && n/2 - 1
			///		SIZE IMPAR: floor(n/2)
			if (size % 2 == 0) // es un tablero par
			{
				// esta en ambos ejes en el centro (2x2 casillas posibles)
				if ((j == size / 2 || j == size / 2 - 1)
					&& (i == size / 2 || i == size / 2 - 1))
					cell->setCenter(true);
			}
			else // es un tablero impar
			{
				// esta en ambos ejes en el centro (1 unica casilla posible)
				// como ambos son ints, la division devuelve el entero redondeando hacia abajo siempre!
				if (j == size / 2 && i == size / 2)
					cell->setCenter(true);
			}

			/// ESQUINA:
			int n = size - 1;
			if ((j == 0 && i == 0) // 0,0
				|| (j == 0 && i == n) // 0,n
				|| (j == n && i == n) // n,n
				|| (j == n && i == 0)) // n,0
				cell->setCorner(true);

			/// ADYACENTES:
			std::array<Cell*, ADJACENTS> adj;
			// inicializa a nullptr
			for (int m = 0; m < ADJACENTS; m++)
				adj[m] = nullptr;

			if (j > 0)
				adj[Effects::Up] = _board[i][j - 1]->getComponent<Cell>();
			if (i < n)
				adj[Effects::Right] = _board[i + 1][j]->getComponent<Cell>();
			if (j < n)
				adj[Effects::Down] = _board[i][j + 1]->getComponent<Cell>();
			if (i > 0)
				adj[Effects::Left] = _board[i - 1][j]->getComponent<Cell>();

			cell->setAdjacents(adj);
		}
	}
}
