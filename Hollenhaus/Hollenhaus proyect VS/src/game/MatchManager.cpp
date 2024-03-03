#include "MatchManager.h"

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
