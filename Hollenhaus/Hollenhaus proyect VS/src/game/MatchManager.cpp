#include "pch.h"
#include "MatchManager.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "BoardManager.h"

#include <iostream>

#include "Manager.h"
#include "MatchOverState.h"
#include "TextComponent.h"
#include "SpriteRenderer.h"


MatchManager::MatchManager(int defaultActionPointsJ1, int defaultActionPointsJ2, TurnState turnStart, BoardManager* bm) :
	board_(bm),
	defaultActionPointsJ1(defaultActionPointsJ1),
	defaultActionPointsJ2(defaultActionPointsJ2),
	actualActionPointsJ1(defaultActionPointsJ1),
	actualActionPointsJ2(defaultActionPointsJ2),
	actualState(turnStart),
	actionPointsVisualJ1(nullptr),
	actionPointsVisualJ2(nullptr),
	actualTurnVisual(nullptr)
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
	if (actualState != Finish && board_ != nullptr)
	{
		if (board_->isFull())
		{
			
			setActualState(Finish);
		}
	}
}

void MatchManager::setActualState(TurnState newState)
{
	actualState = newState;

	switch (actualState)
	{
	case TurnJ1:
#if _DEBUG 
		std::cout << "Nuevo turno: Jugador 1" << std::endl; 
#endif
		resetActualActionPoints();	
		break;
	case TurnJ2:
#if _DEBUG 
		std::cout << "Nuevo turno: Jugador 2" << std::endl;
#endif
		resetActualActionPoints();	
		break;
	case Finish:
#if _DEBUG 
		std::cout << "FIN DE LA PARTIDA" << std::endl;
#endif
		setWinnerOnData();
		GameStateMachine::instance()->setState(GameStates::MATCHOVER);
		break;
	default:
		break;
	}

	updateVisuals();
}

int MatchManager::getActualPlayerActualActionPoints()
{
	return getActualState() == TurnJ1 ? 
		getActualActionPointsJ1() : getActualActionPointsJ2();
}

Players::Owner MatchManager::getPlayerTurn() const
{
	switch (actualState)
	{
	case TurnJ1:
		return Players::PLAYER1;
		break;
	case TurnJ2:
		return Players::PLAYER2;
		break;
	case Finish:
		return Players::NONE;
		break;
	default:
		return Players::NONE;
		break;
	}
}

void MatchManager::substractActualPlayerActionPoints(int points)
{
	getActualState() == TurnJ1 ? 
		substractActionPointsJ1(points) : substractActionPointsJ2(points);
	updateVisuals();
}

void MatchManager::updateVisuals()
{
	// Actualiza los puntos de acción restantes de J1
	actionPointsVisualJ1->getComponent<TextComponent>()->setTxt(
		"Puntos de accion:\n" + std::to_string(actualActionPointsJ1));

	// Actualiza los puntos de acción restantes de J2
	actionPointsVisualJ2->getComponent<TextComponent>()->setTxt(
		"Puntos de accion:\n" + std::to_string(actualActionPointsJ2));

	// Actualiza el indicador del propietario del turno actual
	std::string jugador = actualState == TurnJ1 ? "Jugador 1" : "Jugador 2";
	SDL_Color color = actualState == TurnJ1 ? SDL_Color({ 102, 255, 102, 255 }) : SDL_Color({ 255, 102, 255, 255 });
	actualTurnVisual->getComponent<TextComponent>()->setTxt("Turno de:\n" + jugador);
	actualTurnVisual->getComponent<TextComponent>()->setColor(color);
}

void MatchManager::resetActualActionPoints()
{
	actualActionPointsJ1 = defaultActionPointsJ1;
	actualActionPointsJ2 = defaultActionPointsJ2;
	updateVisuals();
}

void MatchManager::setWinnerOnData()
{
	// EMPATE
	if (board_->getPlayer1Points() == board_->getPlayer2Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinnerOnData(1);
	}

	// JUGADOR 1
	if (board_->getPlayer1Points() > board_->getPlayer2Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinnerOnData(2);
	}

	// JUGADOR 2
	else if (board_->getPlayer2Points() > board_->getPlayer1Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinnerOnData(3);
	}
}
