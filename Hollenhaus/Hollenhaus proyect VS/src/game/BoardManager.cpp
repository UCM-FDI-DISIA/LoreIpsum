#include "BoardManager.h"
#include "GameStateMachine.h"
#include "Manager.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "DropDetector.h"
#include "CellManager.h"
#include "TextComponent.h"
#include "../Cell.h"
#include "MatchManager.h"


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

bool BoardManager::addCard(ecs::entity_t card, int posX, int posY)
{
	ecs::entity_t cell = _board[posX][posY];
	auto cellCmp = mngr().getComponent<CellManager>(cell);
	bool cardAdded = cellCmp->setCard(card);

	if (cardAdded)
	{
		cardsOnBoard++;
	}

	return cardAdded;
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

bool BoardManager::setCard(int x, int y, Card* c, CellData::Owner o)
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


	auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();
	//Gasta los puntos de accion correspondientes
	matchManager->substractActionPointsJ1(c->getCost());

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
			if (_board[i][j]->getComponent<Cell>()->getOwner() == CellData::PLAYER1)
				pPlayer1 += _board[i][j]->getComponent<Cell>()->getTotalValue();
			//si es el jugador 2 (normalmente npc)
			else if (_board[i][j]->getComponent<Cell>()->getOwner() == CellData::PLAYER2)
				pPlayer2 += _board[i][j]->getComponent<Cell>()->getTotalValue();
		}
	}

	scoreVisualJ1->getComponent<TextComponent>()->setTxt(std::to_string(pPlayer1));
	scoreVisualJ2->getComponent<TextComponent>()->setTxt(std::to_string(pPlayer2));
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
				adj[CellData::Up] = _board[i][j - 1]->getComponent<Cell>();
			if (i < n)
				adj[CellData::Right] = _board[i + 1][j]->getComponent<Cell>();
			if (j < n)
				adj[CellData::Down] = _board[i][j + 1]->getComponent<Cell>();
			if (i > 0)
				adj[CellData::Left] = _board[i - 1][j]->getComponent<Cell>();

			cell->setAdjacents(adj);
		}
	}


	// Textos de puntuacion (WIP)
	scoreVisualJ1 = Instantiate(Vector2D(sdlutils().width() - 100, sdlutils().height() * 2 / 3 - 50));
	scoreVisualJ2 = Instantiate(Vector2D(sdlutils().width() - 100, sdlutils().height() / 3 + 25));
	scoreVisualJ1->addComponent<TextComponent>("0", "8bit_32pt", SDL_Color({ 102, 255, 102, 255 }), 120, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	scoreVisualJ2->addComponent<TextComponent>("0", "8bit_32pt", SDL_Color({ 255, 102, 255, 255 }), 120, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	scoreVisualJ1->setLayer(9);
	scoreVisualJ2->setLayer(9);
}
