#include "MatchManager.h"
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
