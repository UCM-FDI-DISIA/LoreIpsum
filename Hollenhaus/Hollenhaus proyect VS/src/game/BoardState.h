#pragma once

#include "GameState.h"
#include "Board.h"
#include "../MatchManager.h"

/// <summary>
/// Estado para probar la logica de la batalla de cartas
/// </summary>

class BoardState : public GameState
{
	Board* board;
	MatchManager* matchManager;

public:

	BoardState();
	~BoardState() override;

	void update() override;
	void render()const  override;
	void refresh() override;

	bool onEnter();
	bool onExit();

	// input ronyoso
	void inputCard();
};


