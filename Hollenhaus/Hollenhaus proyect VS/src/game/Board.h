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
	// lista con las cartas del mazo
	std::vector<Card*> mazo;
	// lista bidimensional para el grid (vector de vectores)
	std::vector<std::vector<Cell*>> grid;

	// inicia un grid (se crea cada carta aqui)
	void initGrid();
	void resetGrid();
	void deleteGrid();
	void applyAllEffects();

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
	bool setCard(int x, int y, Card* c, Owner o); // true si pudo poner carta (no hab�a otra ya antes)

	///
	void countPoints();							//cuenta la puntuacion de ambos jugadores
	void paintBoard();							// pinta el grid
	bool isPlayer(int i, int j, Owner player);	// devuelve si en la posicion indicada esta ocupada por el player indicado
};
