#pragma once

class MatchManager
{
private:

	// score player 1 & 2
	int playerScore = 0;
	int opponentScore = 0;

public:

	// bool matchWon

	// aumenta la puntuacion del jugador
	void increasePlayerScore(int add) {
		playerScore += add;
	}

	// aumenta la puntuacion del oponente
	void increaseOppentScore(int add) {
		playerScore += add;
	}
};

