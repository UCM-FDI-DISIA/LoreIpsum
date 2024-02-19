#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include "../Card.h"
#include "../Cell.h"

class Board {
	int width, height;
	// lista con las cartas del mazo
	std::vector<Card*> mazo;
	// lista bidimensional para el grid (vector de vectores)
	std::vector<std::vector<Cell*>> grid;

	int pPlayer1, pPlayer2;

	// cells temporales
	Cell* cell1;
	Cell* cell2;
	Cell* cell3;

	// inicia un grid (se crea cada carta aqui)
	void IniciaTablero();

public: 
	Board();
	~Board();

	// getters
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	Cell* getCell(int x, int y) const { return grid[x][y]; }
	int getP1Points() { return pPlayer1; }
	int getP2Points() { return pPlayer2; }

	// setters
	void setCell(int x, int y, Cell* c) { grid[x][y] = c; }
	bool setCard(int x, int y, Card* c, Owner o); // true si pudo poner carta (no había otra ya antes)

	// devuelve la informacion de la carra en el formato:
	// [valor/coste/efecto]
	std::string getCellInfo(Cell *cell);

	// devuelve la informacion del efecto en el formato:
	// ->+2  ;;; ->/<-/^/v   ;;;; +/-    ;;;; 
	std::string getEffects(Cell *cell);

	void CountPoints();					// cuenta la puntuacion de ambos jugadores
	void PaintBoard();					// pinta el grid
};
