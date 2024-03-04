#include "MatchManager.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "BoardManager.h"

#include <iostream>

MatchManager::MatchManager(int defaultActionPoints, TurnState turnStart) :
	defaultActionPoints(defaultActionPoints),
	actualActionPoints(defaultActionPoints),
	actualState(turnStart)
{

}

MatchManager::~MatchManager()
{
}

void MatchManager::initComponent()
{
}

void MatchManager::update()
{
	if (actualState != Finish && board_ != nullptr) {
		if (board_->isFull()) {
			setWinner();
			SetActualState(Finish);
		}
	}
}

void MatchManager::SetActualState(TurnState newState)
{
	actualState = newState;

	switch (actualState)
	{
	case MatchManager::TurnJ1:
		ResetActualActionPoints();
		std::cout << "Nuevo turno: Jugador 1" << std::endl;
		break;
	case MatchManager::TurnJ2:
		ResetActualActionPoints();
		std::cout << "Nuevo turno: Jugador 2" << std::endl;
		break;
	case MatchManager::Finish:
		std::cout << "FIN DE LA PARTIDA" << std::endl;
		break;
	default:
		break;
	}
}

CellData::Owner MatchManager::GetPlayerTurn() const
{
	switch (actualState)
	{
	case MatchManager::TurnJ1:
		return CellData::PLAYER1;
		break;
	case MatchManager::TurnJ2:
		return CellData::PLAYER2;
		break;
	case MatchManager::Finish:
		return CellData::NONE;
		break;
	default:
		return CellData::NONE;
		break;
	}
}

void MatchManager::ResetActualActionPoints()
{
	actualActionPoints = defaultActionPoints;
}

void MatchManager::setWinner()
{
	// JUGADOR 1
	if (board_->getPlayer1Points() > board_->getPlayer2Points()) {
		GameStateMachine::instance()->getCurrentState()->setWinner(2);
	}

	// JUGADOR 2
	else if (board_->getPlayer2Points() > board_->getPlayer1Points()) {
		GameStateMachine::instance()->getCurrentState()->setWinner(3);
	}

	// EMPATE
	else if (board_->getPlayer1Points() == board_->getPlayer2Points()) {
		GameStateMachine::instance()->getCurrentState()->setWinner(1);
	}
}