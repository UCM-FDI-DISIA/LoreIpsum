#pragma once

#include "GameState.h"
#include "Board.h"

/// <summary>
/// Estado para probar la logica de la batalla de cartas
/// </summary>

class BoardState : public GameState
{
public:

	BoardState();
	~BoardState();
	void update() override;
	void render() override;
	void refresh() override;
	bool onEnter();
	bool onExit();
private:

	// puntero al tablero
	Board* board;
	
};


