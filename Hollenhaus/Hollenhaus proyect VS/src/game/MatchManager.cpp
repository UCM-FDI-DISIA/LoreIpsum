#include "MatchManager.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "BoardManager.h"

#include <iostream>

#include "Manager.h"
#include "TextComponent.h"

MatchManager::MatchManager(int defaultActionPoints, TurnState turnStart) :
	defaultActionPoints(defaultActionPoints),
	actualActionPointsJ1(defaultActionPoints),
	actualActionPointsJ2(defaultActionPoints),
	actualState(turnStart)
{
}

MatchManager::~MatchManager()
{
}

void MatchManager::initComponent()
{
	actualText = Instantiate(Vector2D(sdlutils().width() - 100, sdlutils().height() / 2));
	actualText->setLayer(1);
	//actualText->addComponent<SpriteRenderer>("black_box"); le queria poner un fondo negro pero que cojones es imposible centrarlo?

	//guarrada MAXIMA:
	auto fondo = Instantiate(actualText->getComponent<Transform>()->getGlobalPos() + Vector2D(-100, -50));
	fondo->addComponent<SpriteRenderer>("black_box");
	auto trasFondo = fondo->getComponent<Transform>(); // je ;)
	//trasFondo->getRelativePos().set(Vector2D(-300, -150)); esto no funca
	//trasfondo->getGlobalPos().set(sdlutils().width() - 500, sdlutils().height() / 2 - 500); esto tampoco!!!? soy tonta o algo
	trasFondo->getGlobalScale().set(2.0, 0.7);
	fondo->setLayer(0);

	const std::string jugador = actualState == TurnJ1 ? "Jugador 1" : "Jugador 2";
	const SDL_Color color = actualState == TurnJ1 ? 
		SDL_Color({102, 255, 102, 255}) :
		SDL_Color({255, 102, 255, 255});
	actualText->addComponent<TextComponent>("Turno de:\n" + jugador,
	                                        "8bit_16pt", SDL_Color({255, 255, 255, 255}), 200,
	                                        TextComponent::BoxPivotPoint::CenterBot,
	                                        TextComponent::TextAlignment::Center
	)->setColor(color);
	setTurnText();
}

void MatchManager::update()
{
	if (actualState != Finish && board_ != nullptr)
	{
		if (board_->isFull())
		{
			setWinner();
			getActualState(Finish);
		}
	}
}

void MatchManager::getActualState(TurnState newState)
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
		break;
	default:
		break;
	}

	setTurnText();
}

CellData::Owner MatchManager::getPlayerTurn() const
{
	switch (actualState)
	{
	case TurnJ1:
		return CellData::PLAYER1;
		break;
	case TurnJ2:
		return CellData::PLAYER2;
		break;
	case Finish:
		return CellData::NONE;
		break;
	default:
		return CellData::NONE;
		break;
	}
}

void MatchManager::setTurnText()
{
	// un mierdon pero el hito es en un dia
	const std::string jugador = actualState == TurnJ1 ? "Jugador 1" : "Jugador 2";
	const SDL_Color color = actualState == TurnJ1 ? 
		SDL_Color({102, 255, 102, 255}) :
		SDL_Color({255, 102, 255, 255});
	actualText->getComponent<TextComponent>()->setTxt("Turno de:\n" + jugador);
	actualText->getComponent<TextComponent>()->setColor(color);
}

void MatchManager::resetActualActionPoints()
{
	actualActionPoints = defaultActionPoints;
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
