#include <../pchs/pch.h>
#include "MultiplayerGameState.h"

#include <SDL.h>
#include "../components/Drag.h"
#include "../components/managers/CardStateManager.h"
#include "../components/managers/DragManager.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../factories/Factory.h"
#include "../factories/CardFactory_v0.h"
#include "../factories/CardFactory_v1.h"
#include "../factories/BoardFactory_v0.h"
#include "../factories/MatchStateUIFactory_v0.h"
#include "../components/managers/MatchManager.h"
#include "../components/managers/BoardManager.h"
#include "../components/basics/TextComponent.h"
#include "../components/managers/MatchManager.h"
#include "../components/EndTurnButton.h"
#include "../components/NPC.h"

#include "../components/managers/IA_manager.h"

#include "../components/managers/Manager.h"
#include "../GameStateMachine.h"
#include "../components/managers/PlayerCardsManager.h"

#include "../components/multiplayer/NetGame.h"

MultiplayerGameState::MultiplayerGameState()
{
	TuVieja("Loading MultiplayerGameState");
}

MultiplayerGameState::~MultiplayerGameState()
{
}

void MultiplayerGameState::refresh()
{
	GameState::refresh();
}

void MultiplayerGameState::update()
{
	GameState::update();
}

void MultiplayerGameState::render() const
{
	GameState::render();
}

void MultiplayerGameState::onEnter()
{
	TuVieja("ENTER MultiplayerGameState");


#pragma region Juego base


	auto factory = new Factory();
	factory->SetFactories(
		static_cast<BoardFactory*>(new BoardFactory_v0(4)),
		static_cast<CardFactory*>(new CardFactory_v1()),
		static_cast<MatchStateUIFactory*>(new MatchStateUIFactory_v0())
	);

	// Factoría del tablero. Generamos el tablero de juego.
	ecs::entity_t boardEntity = factory->createBoard();
	BoardManager* boardManagerComponent = boardEntity->getComponent<BoardManager>();

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	ecs::entity_t matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	MatchManager* matchManagerComponent = matchManager->addComponent<MatchManager>(
		4, 4, Turns::J1, boardManagerComponent);


	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t dragManager = Instantiate();
	dragManager->addComponent<DragManager>();
	dragManager->getComponent<DragManager>()->setBoardManager(boardManagerComponent);
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::DRAG_MANAGER, dragManager);


	// UI 
	ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(100, 500);
	ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(600, 200, 200, 180);
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(170, 265);

	ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);

	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(700, 350, {102, 255, 255, 255});
	ecs::entity_t visual_ScoreCounterJ2 = factory->createVisual_ScoreCounter(700, 225, {255, 102, 255, 255});

	ecs::entity_t visual_BackgroundBoard = factory->createVisual_BackgroundFullImage();


	// Enlazado de la UI con los scripts que la controlan
	matchManagerComponent->setActualTurnVisual(visual_PlayerTurnIndicator);
	matchManagerComponent->setActionPointsVisualJ1(visual_ActionPointsJ1);
	matchManagerComponent->setActionPointsVisualJ2(visual_ActionPointsJ2);
	matchManagerComponent->updateVisuals();

	boardManagerComponent->setScoreVisualJ1(visual_ScoreCounterJ1);
	boardManagerComponent->setScoreVisualJ2(visual_ScoreCounterJ2);
	boardManagerComponent->updateVisuals();


	// incicia la cancion en bucle
	//sdl.musics().at("tryTheme").play();
	//sdlutils().soundEffects().at("battletheme").play(-1);
	//sdlutils().soundEffects().at("battletheme").setChannelVolume(30);


	// Factoría de cartas. Con ella generamos la mano inicial
	ecs::entity_t deckPlayer1 = factory->createDeck();

	ecs::entity_t deckPlayer2 = factory->createDeckJ2Multiplayer();

#pragma endregion


#pragma region Seccion Multiplayer

	//crear la entidad y añadirle el componente
	ecs::entity_t netController = Instantiate();
	NetGame* netGameCmp = netController->addComponent<NetGame>();

	//le decimos al endTurn que existe netGame
	visual_EndTurnButton->getComponent<EndTurnButton>()->setMultiplayer(true);

	//seters de referencias del netGame
	netGameCmp->setMatchManager(matchManagerComponent);
	netGameCmp->setBoardManager(boardManagerComponent);

	netGameCmp->setRivalHand(deckPlayer2->getComponent<PlayerCardsManager>()->getHand());
	netGameCmp->setRivalDeck(deckPlayer2->getComponent<DeckComponent>());

	netGameCmp->setPlayerHand(deckPlayer1->getComponent<PlayerCardsManager>()->getHand());

	//set en el matchManager
	matchManagerComponent->setNetGame(netGameCmp);

	deckPlayer1->getComponent<DeckComponent>()->setNetGame(netGameCmp);

	dragManager->getComponent<DragManager>()->setNetGame(netGameCmp);

#pragma endregion
}

void MultiplayerGameState::onExit()
{
	TuVieja("EXIT MultiplayerGameState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();

	mngr().Free();
}
