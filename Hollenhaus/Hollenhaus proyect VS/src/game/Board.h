#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include "../Card.h"
#include "../Cell.h"

class Board {

public: 

	Board();
	~Board();

	// pinta el tablero
	void PaintBoard();

	// devuelve la informacion de la carra en el formato:
	// [valor/coste/efecto]
	std::string GetCard(Card *card);

	// devuelve la informacion del efecto en el formato:
	// ->+2  ;;; ->/<-/^/v   ;;;; +/-    ;;;; 
	std::string getEffect(Card *card);

	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}

	Cell* getCell(int x, int y) {
		return tablero[x][y];
	}
	

private:

	Cell* cell1;
	Cell* cell2;
	Cell* cell3;

	// inicia un tablero (se crea cada carta aqui)
	void IniciaTablero();

	int width, height;

	// lista con las cartas del mazo
	std::vector<Card*> mazo;

	// lista bidimensional para el tablero (vector de vectores)
	std::vector<std::vector<Cell*>> tablero;

};
