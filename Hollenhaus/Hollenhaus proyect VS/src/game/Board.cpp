#include "Board.h"
#include <iostream>
#include <stdLib.h>

Board::Board(int s) : size(s)
{
	initGrid();
}

Board::~Board()
{
	deleteGrid();
}

/// DEBUG ONLY: Pinta el tablero en consola
void Board::paintBoard()
{
	// para colorear poner 
	// system("Color E4");
	// siendo E el color de fondo y 4 el del texto
	// despues poner de vuelta el 
	// system("Color 07") para blanco y negro

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	// recorre todas las casillas del grid y pinta las cartas
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			// si la casilla no esta vacia
			if (grid[i][j]->getCard() != nullptr)
			{
				if (grid[i][j]->getPlayer() == PLAYER1) // gestiona el color
					SetConsoleTextAttribute(hConsole, 33);
				else if (grid[i][j]->getPlayer() == PLAYER2)
					SetConsoleTextAttribute(hConsole, 26);

				std::cout << getCellInfo(grid[i][j]); // pinta la carta
				std::cout << grid[i][j]->getCorner();
				std::cout << grid[i][j]->getCenter();
				SetConsoleTextAttribute(hConsole, 15);
				//system("Color 07");	// vuelve al negro
			}
			else // si la casilla esta vacia
			{
				std::cout << "[ -/-/-- ]";
				std::cout << grid[i][j]->getCorner();
				std::cout << grid[i][j]->getCenter();
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
}

/// Devuelve si una carta dada por las coordenadas i, j es controlada por el jugador 'player'
bool Board::isPlayer(int i, int j, Owner player)
{
	return grid[i][j]->getPlayer() == player;
}

///  Juega una carta del jugador 'o' en la celda de posicion x, y del tablero
bool Board::setCard(int x, int y, Card* c, Owner o)
{
	const auto cell = grid[x][y];
	if (cell->getCard() != nullptr)
		return false;
	cell->setCard(c, o);
	cell->addEffect(c->getEffect(0));
	applyAllEffects();
	return true;
}


/// DEBUG ONLY: Devuelve un string con los datos de la carta de la celda;
std::string Board::getCellInfo(Cell* cell) const
{
	const auto card = cell->getCard();
	int diff = cell->getTotalValue() - card->getValue();
	char sign = '+';
	if (diff < 0)
		sign = '-';
	std::string info = "[ "
		+ std::to_string(card->getCost()) + "/"
		+ std::to_string(card->getValue()) + "/"
		+ sign
		+ std::to_string(diff) + 
		" ]";

	return info;
}

/// Devuelve los efectos aplicados en una celda dada
std::list<SDLEventCallback> Board::getEffects(Cell* cell) const
{
	return cell->getEffects();
}


/// Metodo para generar un tablero ejemplo inicial
void Board::initGrid()
{
	resetGrid();
	//...;
}


/// Metodo que borra el tablero y lo reinicializa con casillas vacias
void Board::resetGrid()
{
	grid.clear();

	// rellena el tablero de casillas vacias
	std::vector<Cell*> line;
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
			line.push_back(new Cell());
		grid.push_back(line);
		line.clear();
	}

	// asigna valores de esquina, centro y adyacentes
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			/// CENTRO:
			///		SIZE PAR: n/2 && n/2 - 1
			///		SIZE IMPAR: floor(n/2)
			if (size % 2 == 0) // es un tablero par
			{
				// esta en ambos ejes en el centro (2x2 casillas posibles)
				if ((j == size / 2 || j == size / 2 - 1)
					&& (i == size / 2 || i == size / 2 - 1))
					grid[i][j]->setCenter(true);
			}
			else // es un tablero impar
			{
				// esta en ambos ejes en el centro (1 unica casilla posible)
				// como ambos son ints, la division devuelve el entero redondeando hacia abajo siempre!
				if (j == size / 2 && i == size / 2)
					grid[i][j]->setCenter(true);
			}

			/// ESQUINA:
			int n = size - 1;
			if ((j == 0 && i == 0) // 0,0
				|| (j == 0 && i == n) // 0,n
				|| (j == n && i == n) // n,n
				|| (j == n && i == 0)) // n,0
				grid[i][j]->setCorner(true);

			/// ADYACENTES:
			std::array<Cell*, 4> adj;
			// inicializa a nullptr
			for (int i = 0; i < 4; i++)
				adj[i] = nullptr;
			
			if (j > 0)
				adj[Arriba]		= grid[i][j - 1];
			if (i < n)
				adj[Derecha]	= grid[i + 1][j];
			if (j < n)
				adj[Abajo]		= grid[i][j + 1];
			if (i > 0)
				adj[Izquierda]	= grid[i - 1][j];

			grid[i][j]->setAdjacents(adj);
		}
	}
}

/// Metodo para borrar todas las celdas del tablero
void Board::deleteGrid()
{
	grid.clear();
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			delete grid[j][i];
}

void Board::applyAllEffects()
{
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (grid[j][i]->getCard() != nullptr) {
				grid[j][i]->setTotalValue(0);
			}
		}
	}

	//
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (grid[j][i]->getCard() != nullptr) {
				grid[j][i]->applyValue(grid[j][i]->getCard());
			}
		}
	}
}
