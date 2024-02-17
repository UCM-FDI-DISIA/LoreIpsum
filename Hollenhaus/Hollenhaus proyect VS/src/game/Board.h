#pragma once

#include <string>
#include <vector>
#include "../Card.h"


class Board {

public: 

	Board();

	// pinta el tablero
	void PaintBoard();

	// devuelve la informacion de la carra en el formato:
	// [valor/coste/efecto]
	std::string GetCard(Card *card);

	// devuelve la informacion del efecto en el formato:
	// ->+2  ;;; ->/<-/^/v   ;;;; +/-    ;;;; 
	std::string getEffect(Card *card);

private:

	// lista con las cartas del mazo
	std::vector<Card*> mazo;

	// inicia un tablero (se crea cada carta aqui)
	void IniciaTablero();

	int width, height;
};
