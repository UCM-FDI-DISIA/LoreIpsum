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
	actualState(turnStart)
{
}

MatchManager::~MatchManager()
{
}

void MatchManager::initComponent()
{
	/// TURNO VISUAL
	actualTurnVisual = Instantiate(Vector2D(sdlutils().width() - 100, sdlutils().height() / 2 + 25));
	actualTurnVisual->setLayer(2);
	//actualTurnVisual->addComponent<SpriteRenderer>("black_box"); le queria poner un fondo negro pero que cojones es imposible centrarlo?

	//guarrada MAXIMA:
	auto fondo = Instantiate(Vector2D(sdlutils().width() - 200, sdlutils().height() / 2 - 100));
	fondo->addComponent<SpriteRenderer>("black_box");
	auto trasFondo = fondo->getComponent<Transform>(); // je ;)
	trasFondo->getGlobalScale().set(2.0, 1.8);
	fondo->setLayer(1);

	const std::string jugador = actualState == TurnJ1 ? "Jugador 1" : "Jugador 2";
	const SDL_Color color = actualState == TurnJ1 ? SDL_Color({102, 255, 102, 255}) : SDL_Color({255, 102, 255, 255});
	actualTurnVisual->addComponent<TextComponent>("Turno de:\n" + jugador,
	                                              "8bit_32pt", SDL_Color({255, 255, 255, 255}), 200,
	                                              TextComponent::BoxPivotPoint::CenterBot,
	                                              TextComponent::TextAlignment::Center
	)->setColor(color);

	/// AP VISUAL
	const auto matchManager = mngr().getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();
	const int apValueJ1 = matchManager->getActualActionPointsJ1();
	actionPointsVisualJ1 = Instantiate(Vector2D(100, sdlutils().height() - 80));
	actionPointsVisualJ1->addComponent<TextComponent>("Puntos de accion:\n" + std::to_string(apValueJ1),
	                                                  "8bit_24pt", SDL_Color({255, 255, 0, 255}), 200,
	                                                  TextComponent::BoxPivotPoint::CenterCenter,
	                                                  TextComponent::TextAlignment::Center);

	const int apValueJ2 = matchManager->getActualActionPointsJ2();
	actionPointsVisualJ2 = Instantiate(Vector2D(100, 80));
	actionPointsVisualJ2->addComponent<TextComponent>("Puntos de accion:\n" + std::to_string(apValueJ2),
	                                                  "8bit_24pt", SDL_Color({255, 255, 0, 255}), 200,
	                                                  TextComponent::BoxPivotPoint::CenterCenter,
	                                                  TextComponent::TextAlignment::Center);
	actionPointsVisualJ1->setLayer(9);
	actionPointsVisualJ2->setLayer(9);

	setTurnText();
}

void MatchManager::update()
{
	if (actualState != Finish && board_ != nullptr)
	{
		if (board_->isFull())
		{
			setWinner();
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
		resetActualActionPoints();
		std::cout << "Nuevo turno: Jugador 1" << std::endl;
		break;
	case TurnJ2:
		resetActualActionPoints();
		std::cout << "Nuevo turno: Jugador 2" << std::endl;
		break;
	case Finish:
		std::cout << "FIN DE LA PARTIDA" << std::endl;
		GameStateMachine::instance()->setState(GameStates::MATCHOVER);
		break;
	default:
		break;
	}

	setTurnText();
}

int MatchManager::getActivePlayerActualActionPoints()
{
	if (getActualState() == TurnJ1)
		return getActualActionPointsJ1();
	return getActualActionPointsJ2();
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
	/// AP
	const int actionPointsValueJ1 = mngr().getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->
	                                       getActualActionPointsJ1();
	actionPointsVisualJ1->getComponent<TextComponent>()->setTxt(
		"Puntos de accion:\n" + std::to_string(actionPointsValueJ1));

	const int actionPointsValueJ2 = mngr().getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->
	                                       getActualActionPointsJ2();
	actionPointsVisualJ2->getComponent<TextComponent>()->setTxt(
		"Puntos de accion:\n" + std::to_string(actionPointsValueJ2));
}

void MatchManager::setTurnText()
{
	// un mierdon pero el hito es en un dia
	const std::string jugador = actualState == TurnJ1 ? "Jugador 1" : "Jugador 2";
	const SDL_Color color = actualState == TurnJ1 ? SDL_Color({102, 255, 102, 255}) : SDL_Color({255, 102, 255, 255});
	actualTurnVisual->getComponent<TextComponent>()->setTxt("Turno de:\n" + jugador);
	actualTurnVisual->getComponent<TextComponent>()->setColor(color);
}

void MatchManager::resetActualActionPoints()
{
	actualActionPointsJ1 = defaultActionPointsJ1;
	actualActionPointsJ2 = defaultActionPointsJ2;
	updateVisuals();
}

void MatchManager::setWinner()
{
	// JUGADOR 1
	if (board_->getPlayer1Points() > board_->getPlayer2Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinner(2);
	}

	// JUGADOR 2
	else if (board_->getPlayer2Points() > board_->getPlayer1Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinner(3);
	}

	// EMPATE
	else if (board_->getPlayer1Points() == board_->getPlayer2Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinner(1);
	}
}
