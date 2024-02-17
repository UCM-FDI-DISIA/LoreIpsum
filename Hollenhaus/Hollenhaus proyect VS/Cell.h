#pragma once
class Cell
{
	bool isActive;

	// true si la casilla contiene una carta puesta por el player
	bool isPlayer; // Nieves: he dejado el de la carta porq no se si ines lo estaba usando

public:
	bool getPlayer() {
		return isPlayer;
	}
};

