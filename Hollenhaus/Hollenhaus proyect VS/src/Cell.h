#pragma once

#include "Card.h"

class Cell
{
	bool isActive;

	// true si la casilla contiene una carta puesta por el player
	bool isPlayer; // Nieves: he dejado el de la carta porq no se si ines lo estaba usando

	Card* card;

public:

	Cell(Card* card);


	bool getPlayer() {
		return isPlayer;
	}

	bool IsActive() {
		return isActive;
	}
};

