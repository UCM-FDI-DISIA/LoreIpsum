#include "Board.h"
#include <iostream>
#include <stdLib.h>

Board::Board()
{
	width = 4;
	height = 4;

	IniciaTablero();

	cell1 = nullptr;
	cell2 = nullptr;
	cell3 = nullptr;

	// prepara el color para consola con Windows.h
	//HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
}

Board::~Board()
{
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			delete grid[j][i];
}


void Board::paintBoard()
{
	Card* card = nullptr;
	// para colorear poner 
	// system("Color E4");
	// siendo E el color de fondo y 4 el del texto
	// despues poner de vuelta el 
	// system("Color 07") para blanco y negro

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	// recorre todas las casillas del grid y pinta las cartas
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// si la casilla no esta vacia
			if (grid[i][j]->getCard() != nullptr)
			{
				if (grid[i][j]->getPlayer() == PLAYER1) // gestiona el color
					SetConsoleTextAttribute(hConsole, 33);
				else if (grid[i][j]->getPlayer() == PLAYER2)
					SetConsoleTextAttribute(hConsole, 26);

				std::cout << getCellInfo(grid[i][j]); // pinta la carta

				SetConsoleTextAttribute(hConsole, 15);
				//system("Color 07");	// vuelve al negro
			}
			else // si la casilla esta vacia
			{
				std::cout << "[ -/-/---- ]";
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
}

bool Board::isPlayer(int i, int j, Owner player)
{
	return grid[i][j]->getPlayer() == player;
}


bool Board::setCard(int x, int y, Card* c, Owner o)
{
	Cell* cell = grid[y][x];
	if (cell->getCard() != nullptr)
		return false;
	cell->setCard(c, o);
	cell->applyValue(c);
	return true;
}

std::string Board::getCellInfo(Cell* cell)
{
	std::string info = "["
		+ std::to_string(cell->getCard()->getCost()) + "/"
		+ std::to_string(cell->getCard()->getValue()) + "/"
		+ cell->getCard()->getSkill()
		+ "]";

	return info;
}

std::string Board::getEffects(Cell* cell)
{
	return cell->getEffectHistory();
}

void Board::IniciaTablero()
{
	std::string effect1 = "->+2";
	std::string effect2 = "<--1";

	std::vector<Cell*> line;
	// todas las casillas se inicializan como propias
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			line.push_back(new Cell());
		}
		grid.push_back(line);
		line.clear();
	}

	
	// añado cartas a posiciones aleatorias
	grid[0][2]->setCard(new Card(0, 1, effect1), PLAYER1);
	grid[2][0]->setCard(new Card(1, 2), PLAYER1);
	grid[0][3]->setCard(new Card(2, 3, effect2), PLAYER2);
	grid[1][0]->setCard(new Card(3, 4), PLAYER2);

	/*
	std::string sprite = "yippie";
	auto card1 = new Card(1, 2, sprite, effect2);
	auto card2 = new Card(0, 3, sprite, effect1);


	cell1 = new Cell();
	cell2 = new Cell(card2, PLAYER1);
	cell3 = new Cell(card1, PLAYER2);

	line.push_back(cell1);
	line.push_back(cell1);
	line.push_back(cell1);
	line.push_back(cell1);

	grid.push_back(line);
	line.clear();

	line.push_back(cell1);
	line.push_back(cell2);
	line.push_back(cell1);
	line.push_back(cell1);

	grid.push_back(line);
	line.clear();

	line.push_back(cell3);
	line.push_back(cell1);
	line.push_back(cell1);
	line.push_back(cell2);

	grid.push_back(line);
	line.clear();

	line.push_back(cell1);
	line.push_back(cell1);
	line.push_back(cell3);
	line.push_back(cell1);

	grid.push_back(line);
	line.clear();


	/*
	std::string skill = "->+2";
	std::string sprite = "yippie";
	Card carta = Card(1, 2, sprite, skill);

	mazo.push_back(&carta);
	*/
}
