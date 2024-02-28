#include "MatchManager.h"

#include "game/Manager.h"

MatchManager::MatchManager() 
{
	matchResult = TIE;
}

MatchManager::~MatchManager()
{
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
	for (int j = 0; j < board.size(); j++) {
		for (int i = 0; i < board.size(); i++) {
				//si es del jugador 1
			if (board[i][j]->getComponent<Cell>()->getOwner() == PLAYER1) {
				pPlayer1 += board[i][j]->getComponent<Cell>()->getTotalValue();
			}
				//si es el jugador 2 (normalmente npc)
			else if (board[i][j]->getComponent<Cell>()->getOwner() == PLAYER2) {
				pPlayer2 += board[i][j]->getComponent<Cell>()->getTotalValue();
			}
		}
	}
}
