#pragma once

#include "Card.h"

class Cell
{
	bool isActive;

	// true si la casilla contiene una carta puesta por el player
	int player; // Nieves: he dejado el de la carta porq no se si ines lo estaba usando
	// 0 nadie; 1 player; 2 enemigo

	Card* card;

public:

	Cell(Card* card);
	Cell(Cell& cell);
	Cell();


	bool getPlayer() {
		return player;
	}

	bool IsActive() {
		return isActive;
	}

	Cell& operator=(const Cell& o) {
		// delete current list in data;
		// deep copy o.data to data here;
		return *this;
	}

};

