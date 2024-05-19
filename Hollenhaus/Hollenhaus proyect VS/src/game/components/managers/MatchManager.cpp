#include <../pchs/pch.h>

#include <iostream>
#include <utility>
#include "MatchManager.h"
#include "BoardManager.h"
#include "Manager.h"
#include "../Button.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"
#include "../../components/basics/TextComponent.h"
#include "../../components/multiplayer/NetGame.h"
#include "game/Data.h"
#include "../Card.h"
#include "game/CaseManager.h"
#include "game/components/ClickableText.h"

MatchManager::MatchManager(int defaultActionPointsJ1, int defaultActionPointsJ2, Turns::State turnStart,
                           BoardManager* bm, std::string j2) :
	actualState(turnStart),
	board_(bm),
	defaultActionPointsJ1(defaultActionPointsJ1),
	defaultActionPointsJ2(defaultActionPointsJ2),
	actualActionPointsJ1(defaultActionPointsJ1),
	actualActionPointsJ2(defaultActionPointsJ2),
	isBoss(false),
	j2_(std::move(j2)),
	actualTurnVisual(nullptr),
	actionPointsVisualJ1(nullptr),
	actionPointsVisualJ2(nullptr)
{
}

MatchManager::~MatchManager()
{
}

void MatchManager::initComponent()
{
	isBoss = j2_ == "6" || j2_ == "7" || j2_ == "8";
}

void MatchManager::update()
{
	if (actualState != Turns::Finish && board_ != nullptr)
	{
		if (board_->isFull())
		{
			//Finaliza la partida cuando se llena el tablero
			setActualState(Turns::Finish);
		}
	}
}

//Aquí poner las transiciones de cambio de turno y fin de la partida
void MatchManager::setActualState(Turns::State newState)
{
	actualState = newState;

	switch (actualState)
	{
	case Turns::J1:
#if _DEBUG
		std::cout << "Nuevo turno: Jugador 1" << std::endl; 
#endif
		resetActualActionPoints();
		break;
	case Turns::J2:
#if _DEBUG
		std::cout << "Nuevo turno: Jugador 2" << std::endl;
#endif
		resetActualActionPoints();
		break;
	case Turns::Finish:
#if _DEBUG
		std::cout << "FIN DE LA PARTIDA" << std::endl;
#endif
		setWinnerOnData();
		if (isBoss
			&& GameStateMachine::instance()->getCurrentState()->getData()->getWinner() == 2) {

			GameStateMachine::instance()->caseMngr()->resetCase();
		}
		InstantiatePanelFinPartida(GameStateMachine::instance()->getCurrentState()->getData()->getWinner());
		break;
	case Turns::IA:
#if _DEBUG
		std::cout << "Turno: IA" << std::endl;
#endif
		startTurnIA();
		break;
	case Turns::J2_MULTIPLAYER:
#if _DEBUG
		std::cout << "Turno: J2_MULTIPLAYER" << std::endl;
#endif
		break;
	default:
		break;
	}

	updateVisuals();
}

int MatchManager::getActualPlayerActualActionPoints()
{
	return getActualState() == Turns::J1 ? getActualActionPointsJ1() : getActualActionPointsJ2();
}

Players::Owner MatchManager::getPlayerTurn() const
{
	switch (actualState)
	{
	case Turns::J1:
		return Players::PLAYER1;
		break;
	case Turns::J2:
		return Players::PLAYER2;
		break;
	case Turns::Finish:
		return Players::NONE;
		break;
	case Turns::IA:
		return Players::IA;
		break;
	case Turns::J2_MULTIPLAYER:
		return Players::PLAYER2_MULTIPLAYER;
		break;
	default:
		return Players::NONE;
		break;
	}
}

void MatchManager::substractActualPlayerActionPoints(int points)
{
	getActualState() == Turns::J1 ? substractActionPointsJ1(points) : substractActionPointsJ2(points);
	updateVisuals();
	// Si la configuracion admite el paso de turno automático
	if (GameStateMachine::instance()->getCurrentState()->getData()->GetAutomaticNextTurn() && getPlayerTurn() ==
		Players::PLAYER1)
		CheckNextTurnAutomatic();
}

void MatchManager::updateVisuals()
{
	//Si queremos meterlo de forma digética es aquí cuando se pueda
	// Actualiza los puntos de acción restantes de J1
	if (actionPointsVisualJ1 != nullptr)
		actionPointsVisualJ1->getComponent<TextComponent>()->setTxt(
			"Puntos de accion:\n" + std::to_string(actualActionPointsJ1));

	// Actualiza los puntos de acción restantes de J2
	if (actionPointsVisualJ2 != nullptr)
		actionPointsVisualJ2->getComponent<TextComponent>()->setTxt(
			"Puntos de accion:\n" + std::to_string(actualActionPointsJ2));

	/// ACTUALIZACION DE IMAGENES
	turnPointsOff();
	turnPointsOn();


	// Actualiza el indicador del propietario del turno actual
	//Habría que Hacer uan diferenciación también cuando recién cambia de turno para la animación
	SDL_Color color = actualState == Turns::J1 ? SDL_Color({102, 255, 102, 255}) : SDL_Color({255, 102, 255, 255});
	if (actualTurnVisual != nullptr)
	{
		std::string jugador = actualState == Turns::J1 ? "Jugador 1" : "Jugador 2";
		actualTurnVisual->getComponent<TextComponent>()->setTxt("Turno de:\n" + jugador);
		actualTurnVisual->getComponent<TextComponent>()->setColor(color);
	}
}

void MatchManager::setIA_Manager(IA_manager* ia)
{
	ia_manager = ia;
}

void MatchManager::setNetGame(NetGame* ng)
{
	netGame = ng;
}

void MatchManager::endTurnIA()
{
	setActualState(Turns::J1);
	// Animacion gira la estatua
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

void MatchManager::startTurnIA()
{
	ia_manager->StartTurn();
}

void MatchManager::changeTurnMultiplayer()
{
	netGame->nextTurn();
}

void MatchManager::InstantiatePanelFinPartida(int winner)
{
	ecs::entity_t panel = Instantiate(Vector2D(0, 0));
	panel->setLayer(1000);
	panel->addComponent<SpriteRenderer>("panelFinPartida");

	ecs::entity_t victoryDefeatText = Instantiate(Vector2D(128, 240));
	victoryDefeatText->setLayer(1002);
	auto text = victoryDefeatText->addComponent<TextComponent>("", Fonts::GROTESK_32, SDL_Color({0, 0, 0, 0}), 200,
	                                                           Text::BoxPivotPoint::CenterCenter,
	                                                           Text::TextAlignment::Center);

	if (winner == 1)
	{
		text->setTxt("EMPATE");
		text->setColor(SDL_Color({0, 0, 255, 0}));
	}
	if (winner == 2)
	{
		text->setTxt("VICTORIA");
		text->setColor(SDL_Color({255, 50, 50, 0}));
	}
	if (winner == 3)
	{
		text->setTxt("DERROTA");
		text->setColor(SDL_Color({255, 50, 50, 0}));
	}


	ecs::entity_t continuarButton = Instantiate(Vector2D(128, 320));
	continuarButton->setLayer(1001);
	continuarButton->addComponent<TextComponent>("CONTINUAR", Fonts::GROTESK_16, SDL_Color({0, 0, 0, 0}), 200,
	                                             Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	continuarButton->addComponent<BoxCollider>();
	continuarButton->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	continuarButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	continuarButton->addComponent<Button>();
	continuarButton->addComponent<ClickableText>(Colors::MIDNIGHT_HOLLENHAUS, Colors::MIDNIGHT_CLICK, Colors::ROJO_HOLLENHAUS);

	if (netGame == nullptr)
	{
		continuarButton->getComponent<Button>()->connectToButton([this]
		{
			GameStateMachine::instance()->setState(GameStates::MATCHOVER);
		});
	}
	else
	{
		continuarButton->getComponent<Button>()->connectToButton([this]
		{
			GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_END_GAME);
		});
	}
}

void MatchManager::CheckNextTurnAutomatic()
{
	if (getActualPlayerActualActionPoints() <= 0)
	{
		auto hand = playerJ1Hand->getHand();

		for (auto e : hand)
		{
			if (e->getCost() == 0)
			{
				for (auto& e : hand)
				{
					delete e;
					e = nullptr;
				}
				return;
			}
		}

		for (auto& e : hand)
		{
			delete e;
			e = nullptr;
		}

		// Si no quedan puntos de accion y no quedan jugadas disponibles, pasamos turno automáticamente
		setActualState(netGame == nullptr ? Turns::IA : Turns::J2_MULTIPLAYER);
	}
}

void MatchManager::turnPointsOff()
{
	for (auto point : actionPointsJ1)
	{
		if (point->getComponent<SpriteRenderer>() != nullptr)
			point->getComponent<SpriteRenderer>()->setOpacity(0);
	}
}

void MatchManager::turnPointsOn()
{
	for (int i = actualActionPointsJ1; i > 0; i--)
	{
		if (actionPointsJ1[i - 1]->getComponent<SpriteRenderer>() != nullptr)
			actionPointsJ1[i - 1]->getComponent<SpriteRenderer>()->setOpacity(255);
	}
}

void MatchManager::turnEveryPointOn()
{

}
