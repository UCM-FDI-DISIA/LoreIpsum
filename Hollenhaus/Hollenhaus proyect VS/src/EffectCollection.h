#pragma once
#include "game/Card.h"
#include "Cell.h"
#include "game/Board.h"

class EffectCollection
{
private:
	Card* card;
	Board* board;
	Cell* cell;


public:

	EffectCollection();

	// ---- TIPOS DE EFECTOS ----
	// añade valor a algunas o todas sus adyacentes
	void addValueAdj(Cell* thisCardCell, Direction direction, int add, bool ultimateArrow);

	// añade valor a la propia carta si esta en centro - si el número de cartas a izq/der/arr/abj son el mismo
	void addValueCenter(Cell* thisCardCell, int add);

	// añade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	void addValueCorner(Cell* thisCardCell, int add);

	// bloquea el efecto de la carta en alguna direccion
	void blockCard(Cell* thisCardCell, Direction direction);

	// indica que esta carta no se puede bloquear
	bool unblockable();								
};

