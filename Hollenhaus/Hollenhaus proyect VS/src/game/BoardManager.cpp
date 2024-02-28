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


			_board[i][j]->getComponent<BoxCollider>()->setSize(
				Vector2D(sdlutils().images().at("card").width() * 0.25,
					(sdlutils().images().at("card").height()) * 0.25));
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
				adj[Arriba] = _board[i][j - 1]->getComponent<Cell>();
			if (i < n)
				adj[Derecha] = _board[i + 1][j]->getComponent<Cell>();
			if (j < n)
				adj[Abajo] = _board[i][j + 1]->getComponent<Cell>();
			if (i > 0)
				adj[Izquierda] = _board[i - 1][j]->getComponent<Cell>();

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
