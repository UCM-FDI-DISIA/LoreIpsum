#pragma once

#include "game//Board.h"

#include "game/ComponentUpdate.h"


class MatchManager : public ComponentUpdate
{
	int pPlayer1 = 0;
	int pPlayer2 = 0;
	int matchResult;
	//Board* board;

public:

	MatchManager();
	~MatchManager();

	enum matchResults {
		PLAYERWON = 0,
		OPPONENTWON = 1,
		TIE = 2
	};

	int getMatchResult() const { return matchResult; }
	int getPlayer1Points() const { return pPlayer1; }
	int getPlayer2Points() const { return pPlayer2; }

	void increasePlayerScore(int add) { pPlayer1 += add; } // aumenta la puntuacion del jugador
	void increaseOppentScore(int add) { pPlayer2 += add; } // aumenta la puntuacion del oponente

	int whoWon();
	void updateScore();

};

