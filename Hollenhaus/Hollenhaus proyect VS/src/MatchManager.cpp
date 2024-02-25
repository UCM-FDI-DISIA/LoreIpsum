#include "MatchManager.h"

MatchManager::MatchManager(Board* board) : board(board)
{
	matchResult = TIE;
}

MatchManager::~MatchManager()
{
	delete board;
}

int MatchManager::whoWon()
{
	if (pPlayer1 > pPlayer2) { return matchResult = PLAYERWON; } // gana player
	if (pPlayer2 > pPlayer1) { return matchResult = OPPONENTWON; } // gana opponent
	if (pPlayer1 == pPlayer2) { return matchResult = TIE; } // empate
}

void MatchManager::updateScore()
{
	// reinicia los valores
	pPlayer1 = 0;
	pPlayer2 = 0;

	// hace recuento de valores
	for (int i = 0; i < board->getSize(); i++) {
		for (int j = 0; j < board->getSize(); j++) {
				//si es del jugador 1
			if (board->isPlayer(i,j, PLAYER1)) {
				pPlayer1 += board->getCell(i,j)->getTotalValue();
			}
				//si es el jugador 2 (normalmente npc)
			else if (board->isPlayer(i, j, PLAYER2)) {
				pPlayer2 += board->getCell(i, j)->getTotalValue();
			}
		}
	}
}
