#include "MatchManager.h"

int MatchManager::whoWon()
{
	if (playerScore > opponentScore) { return matchResult = PLAYERWON; } // gana player
	else if (opponentScore > playerScore) { return matchResult = OPPONENTWON; } // gana opponent
	else if (playerScore = opponentScore) { return matchResult = TIE; } // empate
}