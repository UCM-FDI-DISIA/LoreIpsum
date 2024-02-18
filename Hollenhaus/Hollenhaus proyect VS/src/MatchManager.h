#pragma once

class MatchManager
{
private:
	// score player 1 & 2
	int playerScore = 0;
	int opponentScore = 0;

public:
	int matchResult;

	enum matchResults {
		PLAYERWON = 0,
		OPPONENTWON = 1,
		TIE = 2
	};

	// aumenta la puntuacion del jugador
	void increasePlayerScore(int add) {
		playerScore += add;
	}

	// aumenta la puntuacion del oponente
	void increaseOppentScore(int add) {
		playerScore += add;
	}

	int whoWon();
};

