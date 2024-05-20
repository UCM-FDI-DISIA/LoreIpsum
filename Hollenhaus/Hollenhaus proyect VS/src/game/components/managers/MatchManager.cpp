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
#include "game/SoundManager.h"
#include "game/components/ImageWithFrames.h"

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
	for (int i = 0; i < 4; i++)
	{
		actionPointsJ1[i] = nullptr;
	}
}

MatchManager::~MatchManager()
{

}

void MatchManager::initComponent()
{
	isBoss = j2_ == "6" || j2_ == "7" || j2_ == "8";

	fadeTween =
		tweeny::from(0)
		.to(255)
		.during(15)
		.via(tweeny::easing::linear);
}

void MatchManager::update()
{
	if (actualState != Turns::Finish && board_ != nullptr)
	{
		if (board_->isFull())
		{
			//Finaliza la partida cuando se llena el tablero
			setActualState(Turns::Finish);
			board_->resetVisuals();
		}
	}

	fadeTween.step(1);
	if (fadeTween.progress() >= 1.0) fadeIn = false;
	for (int i = 0; i < 4; i++)
	{
		if (actionPointsJ1[i] == nullptr) continue;

		SpriteRenderer* spr = nullptr;
		if (actionPointsJ1[i]->getComponent<SpriteRenderer>() != nullptr)
			spr = actionPointsJ1[i]->getComponent<SpriteRenderer>();

		if (spr == NULL || spr == nullptr) continue;

		if (fadeIn)
		{
			if (fadeInIndexes[i])
			{
				if (spr->getOpacity() < 255)
					spr->setOpacity(fadeTween.peek());
			}
			else spr->setOpacity(255);
		}
		else
		{
			if (fadeOutIndexes[i])
			{
				if (spr->getOpacity() > 0)
					spr->setOpacity(fadeTween.peek());
			}
		}


		//if (fadeOutIndexes[i]
		//	|| fadeInIndexes[i]
		//)
		//{
		//	if (fadeIn)
		//	{
		//		if (spr != nullptr
		//			&& spr->getOpacity() < 255)
		//			spr->setOpacity(fadeTween.peek());
		//	}
		//	else
		//	{
		//		if (spr != nullptr
		//			&& spr->getOpacity() > 0)
		//			spr->setOpacity(fadeTween.peek());
		//	}
		//}

	}
}

//Aquí poner las transiciones de cambio de turno y fin de la partida
void MatchManager::setActualState(Turns::State newState)
{
	actualState = newState;

	switch (actualState)
	{
	case Turns::J1: {


#if _DEBUG
		std::cout << "Nuevo turno: Jugador 1" << std::endl;
#endif
		resetActualActionPoints();

	}
		break;
	case Turns::J2:
	{
#if _DEBUG
		std::cout << "Nuevo turno: Jugador 2" << std::endl;
#endif
		resetActualActionPoints();
	}
		break;
	case Turns::Finish:
#if _DEBUG
		std::cout << "FIN DE LA PARTIDA" << std::endl;
#endif
		setWinnerOnData();
		if (GameStateMachine::instance()->getCurrentState()->getData()->getWinner() == 2)
		{
			dropCard();
			if(isBoss)
				GameStateMachine::instance()->caseMngr()->resetCase();
		}
		InstantiatePanelFinPartida(GameStateMachine::instance()->getCurrentState()->getData()->getWinner());
		break;
	case Turns::IA:
	{
#if _DEBUG
		std::cout << "Turno: IA" << std::endl;
#endif
		startTurnIA();
	}
		break;
	case Turns::J2_MULTIPLAYER:
#if _DEBUG
		std::cout << "Turno: J2_MULTIPLAYER" << std::endl;
#endif
		break;
	default:
		break;
	}


	changeMusicTurn(actualState);


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
	lastSpentPoints = lastPointsJ1 - actualActionPointsJ1;
	if (lastSpentPoints < 0)
	{
		// ha habido reseteo
		auto pointsWon = actualActionPointsJ1 - lastPointsJ1;
		fadeIn = true;
		lastSpentPoints = 0;
		resetFadeIndexes();
		for (int i = actualActionPointsJ1; i > actualActionPointsJ1 - pointsWon; i--)
			fadeInIndexes[i - 1] = true;

		//for (int i = 0; i < 4; i++)
		//	fadeInIndexes[i] = true;
		startPointsOn();
	}
	else if (lastSpentPoints > 0)
	{
		// se han gastado
		resetFadeIndexes();
		fadeIn = false;
		for (int i = lastPointsJ1; i > actualActionPointsJ1; i--)
		{
			fadeOutIndexes[i - 1] = true;
		}
		startPointsOff();
	}
	lastPointsJ1 = actualActionPointsJ1;

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
	if (endTurnButton!= nullptr)
	{
		if (const auto iwf = endTurnButton->getComponent<ImageWithFrames>())
		{
			iwf->setSprite("estatua_j1", 1, 12, 1);
		}
	}
}

void MatchManager::resetFadeIndexes()
{
	for (int i = 0; i < 4; i++)
	{
		fadeInIndexes[i] = false;
		fadeOutIndexes[i] = false;
	}
}

void MatchManager::resetActualActionPoints()
{
	actualActionPointsJ1 = defaultActionPointsJ1;
	actualActionPointsJ2 = defaultActionPointsJ2;
	updateVisuals();
}

void MatchManager::dropCard()
{
	const int id = sdlutils().npcs().at(j2_).cardToDrop();
	if(id != -1)
		GameStateMachine::instance()->getCurrentState()->addCardToDrawer(id);
}

void MatchManager::setWinnerOnData()
{
	// EMPATE
	if (board_->getPlayer1Points() == board_->getPlayer2Points())
	{
		GameStateMachine::instance()->getCurrentState()->setWinnerOnData(1);
	}

	// JUGADOR 1
	if (board_->getPlayer1Points() > board_->getPlayer2Points()) // Gana el jugador.
	{
		GameStateMachine::instance()->getCurrentState()->setWinnerOnData(2);
		GameStateMachine::instance()->getCurrentState()->setDefeatedNPC(std::stoi(j2_)); // Se supone que stoi convierte el string a int. Espero que si...
		GameStateMachine::instance()->getCurrentState()->saveData(); // Guardar Data para que se escriba el NPC derrotado.
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

	ecs::entity_t victoryDefeatText = Instantiate(Vector2D(sdlutils().width() - 120, 240));
	victoryDefeatText->setLayer(1002);
	auto text = victoryDefeatText->addComponent<TextComponent>("", Fonts::GROTESK_32, Colors::MIDNIGHT_HOLLENHAUS, 200,
	                                                           Text::BoxPivotPoint::CenterCenter,
	                                                           Text::TextAlignment::Center);

	if (winner == 1)
	{
		text->setTxt("EMPATE");
		text->setColor(Colors::AMARILLO_PIS);
	}
	if (winner == 2)
	{
		text->setTxt("VICTORIA");
		text->setColor(Colors::VERDE_BANKIA);
	}
	if (winner == 3)
	{
		text->setTxt("DERROTA");
		text->setColor(Colors::ROJO_HOLLENHAUS);
	}


	ecs::entity_t continuarButton = Instantiate(Vector2D(sdlutils().width() - 120, 310));
	continuarButton->setLayer(1001);
	continuarButton->addComponent<TextComponent>("CONTINUAR", Fonts::GROTESK_24, Colors::MIDNIGHT_HOLLENHAUS, 200,
	                                             Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	continuarButton->addComponent<BoxCollider>();
	continuarButton->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	continuarButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	continuarButton->addComponent<Button>();
	continuarButton->addComponent<
		ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

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

void MatchManager::checkIfAddKey(Card* c)
{
	for(auto& e : c->getEffectsJson())
	{
		const auto state = GameStateMachine::instance()->getCurrentState();
		const int keys = state->getKeys();
		switch (e.type())
		{
		case Effects::Type::Superflecha:
			if(keys == 1)
			{
				state->addKey();
			}
			break;
		case Effects::Type::Centro:
			if(keys == 2)
			{
				state->addKey();
			}
			break;
		case Effects::Type::Esquina:
			if(keys == 3)
			{
				state->addKey();
			}
			break;
		case Effects::Type::Block:
			if(keys == 4)
			{
				state->addKey();
			}
			break;
		case Effects::Type::Unblockable:
			if(keys == 5)
			{
				state->addKey();
			}
			break;
		default:
			break;
		}
	}
}

void MatchManager::changeMusicTurn(Turns::State i)
{
	auto music = SoundManager::instance();

	Musics::MUSIC a = Musics::MUSIC::BATTLE_P_M;
	Musics::MUSIC b = Musics::MUSIC::BATTLE_T_M;

	switch (i)
	{
	case Turns::J1:
		a = Musics::MUSIC::BATTLE_P_M;
		b = Musics::MUSIC::BATTLE_T_M;
		break;
	case Turns::J2:
		a = Musics::MUSIC::BATTLE_P_M;
		b = Musics::MUSIC::BATTLE_T_M;
		break;
	case Turns::Finish:
		a = Musics::MUSIC::BATTLE_P_M;
		b = Musics::MUSIC::BATTLE_T_M;
		break;
	case Turns::IA:
		a = Musics::MUSIC::BATTLE_T_M;
		b = Musics::MUSIC::BATTLE_P_M;
		break;
	case Turns::J2_MULTIPLAYER:
		a = Musics::MUSIC::BATTLE_T_M;
		b = Musics::MUSIC::BATTLE_P_M;
		break;
	default:
		break;
	}

	music->changeDynamicMusic(a,b);


}

void MatchManager::turnPointsOff()
{
	for (auto point : actionPointsJ1)
	{
		if (point == nullptr) continue;
		if (point->getComponent<SpriteRenderer>() != nullptr)
			point->getComponent<SpriteRenderer>()->setOpacity(0);
	}
}

void MatchManager::turnPointsOn()
{
	for (int i = actualActionPointsJ1; i > 0; i--)
	{
		if (actionPointsJ1[i - 1] == nullptr) continue; 
		if (actionPointsJ1[i - 1]->getComponent<SpriteRenderer>() != nullptr)
			actionPointsJ1[i - 1]->getComponent<SpriteRenderer>()->setOpacity(255);
	}
}

void MatchManager::startPointsOn()
{
	turnPointsOff();
	fadeTween =
		tweeny::from(0)
		.to(255)
		.during(15)
		.via(tweeny::easing::linear);
}

void MatchManager::startPointsOff()
{
	fadeTween =
		tweeny::from(255)
		.to(0)
		.during(15)
		.via(tweeny::easing::linear);
}
