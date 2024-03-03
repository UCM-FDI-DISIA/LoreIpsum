#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include "../Cell.h"
#include "Card.h"

class Board {
	int size;
	// lista bidimensional para el tablero (vector de vectores)
	std::vector<std::vector<Cell*>> grid;

	void initGrid();
	void resetGrid();
	void deleteGrid();
	void applyAllEffects() const;

public:
	Board() = default;
	Board(int);
	~Board();

	// getters
	int getSize() const { return size; }
	Cell* getCell(int x, int y) const { return grid[x][y]; }
	std::string getCellInfo(Cell *cell) const; // devuelve la informacion de la carra en el formato: [valor/coste/efecto]
	std::list<SDLEventCallback> getEffects(Cell *cell) const;

	// setters
	void setCell(int x, int y, Cell* c) { grid[x][y] = c; }
	bool setCard(int x, int y, Card* c, CellData::Owner o); // true si pudo poner carta (no habia otra ya antes)

	///
	void paintBoard();									// pinta el grid
	bool isPlayer(int i, int j, CellData::Owner player) const;	// devuelve si en la posicion indicada esta ocupada por el player indicado
};
