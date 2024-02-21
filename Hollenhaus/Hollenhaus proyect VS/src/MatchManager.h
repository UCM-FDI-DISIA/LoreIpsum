#pragma once

#include "game//Board.h"

class MatchManager
{
private:
	// matchManager player 1 & 2
	int pPlayer1 = 0;
	int pPlayer2 = 0;
	int matchResult;

	Board* board;

public:

	MatchManager(Board* board);
	~MatchManager();

	enum matchResults {
		PLAYERWON = 0,
		OPPONENTWON = 1,
		TIE = 2
	};

	int getMatchResult() { return matchResult; }
	int getPlayer1Points() { return pPlayer1; }
	int getPlayer2Points() { return pPlayer2; }

	// aumenta la puntuacion del jugador
	void increasePlayerScore(int add) {
		pPlayer1 += add;
	}
	// aumenta la puntuacion del oponente
	void increaseOppentScore(int add) {
		pPlayer2 += add;
	}

	int whoWon();
	void updateScore();
};

