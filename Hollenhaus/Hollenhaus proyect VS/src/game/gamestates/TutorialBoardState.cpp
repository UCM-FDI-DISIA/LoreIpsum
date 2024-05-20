#include <../pchs/pch.h>

#include "TutorialBoardState.h"
#include <SDL.h>
#include "../components/Drag.h"
#include "../components/managers/CardStateManager.h"
#include "../components/managers/DragManager.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../factories/Factory.h"
#include "../factories/DialogueFactory_V0.h"
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
#include "../SoundManager.h"

#include "../components/managers/IA_manager.h"

#include "../components/managers/Manager.h"
#include "../GameStateMachine.h"
#include "../components/managers/PlayerCardsManager.h"
#include "../TutorialManager.h"
#include "../components/managers/TutorialBoardManager.h"
#include "game/components/ImageWithFrames.h"

TutorialBoardState::TutorialBoardState()
{
	TuVieja("Loading Tutorial Board");
}

TutorialBoardState::~TutorialBoardState()
{
}

void TutorialBoardState::refresh()
{
	GameState::refresh();
}

void TutorialBoardState::update()
{
	GameState::update();
}

void TutorialBoardState::render() const
{
	GameState::render();
}

void TutorialBoardState::onEnter()
{
	TuVieja("ENTRANDO AL TUTORIAL...");


	setBaseEntity();
	initTutorial();
	setBoard();

	tutorial->getComponent<TutorialManager>()->startTutorial();
	tutorial->getComponent<TutorialManager>()->setCurrentTutorial(Tutorials::BOARD);
	tutorial->getComponent<TutorialManager>()->setCurrentTutorialState(Tutorials::Board::BOARD_NONE);
	tutorial->getComponent<TutorialManager>()->setNextTutorialState(Tutorials::Board::INIT);


	int a = tutorial->getComponent<TutorialManager>()->getTutorialState();

	tutorial->getComponent<TutorialBoardManager>()->setObjs(objs);


	auto music = SoundManager::instance();
	music->startDynamicMusic(Sounds::MUSIC::BATTLE_P_M, Sounds::MUSIC::BATTLE_T_M);
}

void TutorialBoardState::onExit()
{
	auto music = SoundManager::instance();
	music->stopDynamicMusic(Sounds::MUSIC::BATTLE_P_M, Sounds::MUSIC::BATTLE_T_M);


	tutorial->getComponent<TutorialManager>()->endTutorial();

	delete factory;

	GameStateMachine::instance()->getMngr()->Free();
}

void TutorialBoardState::setJ2(std::string rival)
{
	j2_ = rival;
}


void TutorialBoardState::setBoard()
{
	TuVieja("\n SETTING TUTORIAL BOARD");

	//TuVieja(sdlutils().dialogues().at("El Xungo del Barrio").Convo(0).Node(3).Text());

	factory = new Factory();
	factory->SetFactories(
		static_cast<BoardFactory*>(new BoardFactory_v0(4)),
		static_cast<CardFactory*>(new CardFactory_v1()),
		static_cast<MatchStateUIFactory*>(new MatchStateUIFactory_v0())
	);

	// Factoria del tablero. Generamos el tablero de juego.
	ecs::entity_t boardEntity = factory->createBoard();
	BoardManager* boardManagerComponent = boardEntity->getComponent<BoardManager>();

	objs.push_back(boardEntity);
	tutorial->getComponent<TutorialBoardManager>()->setCard(boardEntity);

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

	// Factoria de cartas. Con ella generamos la mano inicial
	ecs::entity_t deckPlayer1 = factory->createDeck();
	ecs::entity_t deckPlayer2 = factory->createDeckJ2(j2_);

	objs.push_back(deckPlayer1);
	objs.push_back(deckPlayer2);

	tutorial->getComponent<TutorialBoardManager>()->setDeck(deckPlayer1);





	/// UI ///
	factory->createVisual_BackgroundFullImage();
	/// PUNTOS DE ACCION
	// deprecated:
	// ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(95, 280);
	// deprecated:
	// ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	auto j1Puntos = createPointsJ1();
	auto j2Puntos = createPointsJ2();

	/// BOTON END TURN
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(170, 250);
	objs.push_back(visual_EndTurnButton);
	tutorial->getComponent<TutorialBoardManager>()->setNextTurn(visual_EndTurnButton);

	///// LEYENDA
	//ecs::entity_t visual_KeyButton = factory->createVisual_KeyButton(720, 400);
	//visual_KeyButton->getComponent<Transform>()->addParent(keyTr_);
	//keyTr_->increaseLayer(key_->getLayer());

	/// TURNO Y SCORE
	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(560, 170, 200, 180);
	//ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);
	ecs::entity_t visual_ScoreCounterJ2 = factory->createVisual_ScoreCounter(680, 233, Colors::MORADO_BERENJENA);
	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(680, 313, Colors::MIDNIGHT_LIGHT);


	// Enlazado de la UI con los scripts que la controlan
	//matchManagerComponent->setActualTurnVisual(visual_PlayerTurnIndicator);
	//matchManagerComponent->setActionPointsVisualJ1(visual_ActionPointsJ1);
	//matchManagerComponent->setActionPointsVisualJ2(visual_ActionPointsJ2);
	matchManagerComponent->updateVisuals();

	boardManagerComponent->setScoreVisualJ1(visual_ScoreCounterJ1);
	boardManagerComponent->setScoreVisualJ2(visual_ScoreCounterJ2);
	boardManagerComponent->updateVisuals();


	// Seteamos la mano de J1 en el matchManager
	matchManagerComponent->SetHandComponent(deckPlayer1->getComponent<PlayerCardsManager>()->getHand());


	auto music = SoundManager::instance();
	music->startDynamicMusic(Sounds::MUSIC::BATTLE_P_M, Sounds::MUSIC::BATTLE_T_M);


#pragma region Seccion IA

	//crear la entidad y anyadirle el componente
	ecs::entity_t IA_controler = Instantiate();
	IA_manager* ia_managerComponent = IA_controler->addComponent<IA_manager>();

	//le decimos al endTurn que existe la IA
	visual_EndTurnButton->getComponent<EndTurnButton>()->setIA(true);


	//seters de referencias de la ia

	ia_managerComponent->setMatchManager(matchManagerComponent);
	ia_managerComponent->setBoardManager(boardManagerComponent);

	ia_managerComponent->setPlayerHand(deckPlayer1->getComponent<PlayerCardsManager>()->getHand());
	ia_managerComponent->setEnemyHand(deckPlayer2->getComponent<PlayerCardsManager>()->getHand());

	ia_managerComponent->setPlayerDeck(deckPlayer1->getComponent<DeckComponent>());
	ia_managerComponent->setEnemyDeck(deckPlayer2->getComponent<DeckComponent>());

	//set en el matchManager
	matchManagerComponent->setIA_Manager(ia_managerComponent);


#pragma endregion
}

void TutorialBoardState::setBaseEntity()
{
	base = Instantiate();
	base->addComponent<Transform>();
	//base->getComponent<Transform>()->addParent(nullptr);
	//base->getComponent<Transform>()->getRelativeScale().set(0.25, 0.25);
	Vector2D pos{200, 200};
	base->getComponent<Transform>()->setGlobalPos(pos);
	base->setLayer(2);

	colliderWallBase = Instantiate();
	colliderWallBase->addComponent<Transform>();
	Vector2D pos2{0, 0};
	colliderWallBase->getComponent<Transform>()->setGlobalPos(pos2);
	colliderWallBase->setLayer(2);
}


void TutorialBoardState::initTutorial()
{
	// entidad tutorial para gestionar cositas
	tutorial = Instantiate();

	tutorial->addComponent<TutorialManager>();
	auto manager = tutorial->addComponent<TutorialBoardManager>(base, tutorial);
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::TUTORIAL_MANAGER, tutorial);
}

std::array<ecs::entity_t, 4> TutorialBoardState::createPointsJ1()
{
	std::array<ecs::entity_t, 4> puntosJ1 =
	{
		Instantiate(Vector2D()),
		Instantiate(Vector2D()),
		Instantiate(Vector2D()),
		Instantiate(Vector2D())
	};

	for (auto punto : puntosJ1)
	{
		punto->getComponent<Transform>()->setGlobalScale(0.75f, 0.75f);
		punto->addComponent<SpriteRenderer>("llamitas");
		punto->addComponent<ImageWithFrames>(1, 4, -1, 500);
		//->setCurrentCol(sdlutils().rand().nextInt(0,4);
	}

	puntosJ1[0]->getComponent<Transform>()->setGlobalPos(-48, 388);
	puntosJ1[1]->getComponent<Transform>()->setGlobalPos(5, 320);
	puntosJ1[2]->getComponent<Transform>()->setGlobalPos(52, 385);
	puntosJ1[3]->getComponent<Transform>()->setGlobalPos(13, 450);

	puntosJ1[0]->getComponent<ImageWithFrames>()->setCurrentCol(0);
	puntosJ1[1]->getComponent<ImageWithFrames>()->setCurrentCol(1);
	puntosJ1[2]->getComponent<ImageWithFrames>()->setCurrentCol(2);
	puntosJ1[3]->getComponent<ImageWithFrames>()->setCurrentCol(3);

	return puntosJ1;
}

std::array<ecs::entity_t, 4> TutorialBoardState::createPointsJ2()
{
	std::array<ecs::entity_t, 4> puntosJ2 =
	{
		Instantiate(Vector2D()),
		Instantiate(Vector2D()),
		Instantiate(Vector2D()),
		Instantiate(Vector2D())
	};

	for (auto punto : puntosJ2)
	{
		punto->getComponent<Transform>()->setGlobalScale(0.75f, 0.75f);
		punto->addComponent<SpriteRenderer>("llamitas");
		punto->addComponent<ImageWithFrames>(1, 4, -1, 500);
		//->setCurrentCol(sdlutils().rand().nextInt(0,4);
	}

	puntosJ2[0]->getComponent<Transform>()->setGlobalPos(-15, -48);
	puntosJ2[1]->getComponent<Transform>()->setGlobalPos(70, -48);
	puntosJ2[2]->getComponent<Transform>()->setGlobalPos(-23, 25);
	puntosJ2[3]->getComponent<Transform>()->setGlobalPos(50, 25);

	puntosJ2[0]->getComponent<ImageWithFrames>()->setCurrentCol(3);
	puntosJ2[1]->getComponent<ImageWithFrames>()->setCurrentCol(1);
	puntosJ2[2]->getComponent<ImageWithFrames>()->setCurrentCol(0);
	puntosJ2[3]->getComponent<ImageWithFrames>()->setCurrentCol(2);

	return puntosJ2;
}