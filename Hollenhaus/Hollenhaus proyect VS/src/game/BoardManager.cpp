#include "BoardManager.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "DropDetector.h"
#include "CellManager.h"

#include "../Cell.h"

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

			//PARTE VISUAL
			_board[i][j] = Instantiate(Vector2D(200 + i*100, 100 + j*100), ecs::grp::DROPS);
			auto cellCmp = _board[i][j]->addComponent<CellManager>();
			_board[i][j]->addComponent<BoxCollider>();


			_board[i][j]->addComponent<DropDetector>()->getCardPos().set(Vector2D(200 + i * 100, 100 + j * 100));

			_board[i][j]->getComponent<DropDetector>()->getBoardPos().set(Vector2D(i, j));


			_board[i][j]->getComponent<BoxCollider>()->setSize(
				Vector2D(sdlutils().images().at("card").width() * 0.55,
					(sdlutils().images().at("card").height()) * 0.55));
			cellCmp->setPosOnBoard(i, j);


			
		}
	}

	// Cada elemento de la matriz tiene un nuevo Cell (entidad) vacío
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGTH; j++) {


			Cell* cell = _board[i][j]->addComponent<Cell>();



			/// CENTRO:
			///		SIZE PAR: n/2 && n/2 - 1
			///		SIZE IMPAR: floor(n/2)
			if (WIDTH % 2 == 0) // es un tablero par
			{
				// esta en ambos ejes en el centro (2x2 casillas posibles)
				if ((j == WIDTH / 2 || j == WIDTH / 2 - 1)
					&& (i == WIDTH / 2 || i == WIDTH / 2 - 1))
					cell->setCenter(true);
			}
			else // es un tablero impar
			{
				// esta en ambos ejes en el centro (1 unica casilla posible)
				// como ambos son ints, la division devuelve el entero redondeando hacia abajo siempre!
				if (j == WIDTH / 2 && i == WIDTH / 2)
					cell->setCenter(true);
			}

			/// ESQUINA:
			int n = WIDTH - 1;
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
				adj[CellData::Arriba] = _board[i][j - 1]->getComponent<Cell>();
			if (i < n)
				adj[CellData::Derecha] = _board[i + 1][j]->getComponent<Cell>();
			if (j < n)
				adj[CellData::Abajo] = _board[i][j + 1]->getComponent<Cell>();
			if (i > 0)
				adj[CellData::Izquierda] = _board[i - 1][j]->getComponent<Cell>();

			cell->setAdjacents(adj);

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


Cell* BoardManager::getCell(int x, int y)const  {

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
	cell->setCard(c, o);
	cell->addEffect(c->getEffect(c->getEffectSize() - 1));
	applyAllEffects();
	return true;
}

void BoardManager::updateScore()
{
	// reinicia los valores
	pPlayer1 = 0;
	pPlayer2 = 0;


	//VA AL BOARD MANAGER
	// hace recuento de valores
	for (int j = 0; j < _board.size(); j++) {
		for (int i = 0; i < _board.size(); i++) {
				//si es del jugador 1
			if (_board[i][j]->getComponent<Cell>()->getOwner() == CellData::PLAYER1) {
				pPlayer1 += _board[i][j]->getComponent<Cell>()->getTotalValue();
			}
				//si es el jugador 2 (normalmente npc)
			else if (_board[i][j]->getComponent<Cell>()->getOwner() == CellData::PLAYER2) {
				pPlayer2 += _board[i][j]->getComponent<Cell>()->getTotalValue();
			}
		}
	}
	

}

void BoardManager::applyAllEffects() const
{
	for (int j = 0; j < WIDTH; j++)
		for (int i = 0; i < WIDTH; i++)
			if (_board[j][i]->getComponent<Cell>()->getCard() != nullptr)
				_board[j][i]->getComponent<Cell>()->setTotalValue(0);

	for (int j = 0; j < WIDTH; j++)
		for (int i = 0; i < WIDTH; i++)
			if (_board[j][i]->getComponent<Cell>()->getCard() != nullptr)
				_board[j][i]->getComponent<Cell>()->applyValue(_board[j][i]->getComponent<Cell>()->getCard());
}

