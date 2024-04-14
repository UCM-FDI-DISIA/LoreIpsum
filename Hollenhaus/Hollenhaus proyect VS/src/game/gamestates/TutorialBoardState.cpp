#include "pch.h"
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

#include "../components/managers/IA_manager.h"

#include "../components/managers/Manager.h"
#include "../GameStateMachine.h"
#include "../components/managers/PlayerCardsManager.h"

TutorialBoardState::TutorialBoardState()
{
	TuVieja("Loading Tutorial Board");

	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);
}

TutorialBoardState::~TutorialBoardState()
{

	delete factory;
	factory = nullptr;
}

void TutorialBoardState::refresh()
{
	GameState::refresh();
}

void TutorialBoardState::update()
{
	GameState::update();

	if (actionEnded()) {

		nextTutorialState();

		ended = false;
	}

	updateTutorialState();
}

void TutorialBoardState::render() const
{
	GameState::render();
}

void TutorialBoardState::onEnter()
{

	TuVieja("ENTRANDO AL TUTORIAL...");

	currentState = NONE;
	nextState = INIT;
	ended = false;

	setBoard();
	setBaseEntity();

}

void TutorialBoardState::onExit()
{


}

void TutorialBoardState::updateTutorialState()
{
	if (currentState != nextState) {
		switch (nextState)
		{
		case INIT:
			setINIT();
			break;
		case CARD:
			setCARD();
			break;
		default:
			break;
		}

		currentState = nextState;
	}
}

bool TutorialBoardState::actionEnded()
{
	return ended;
}

void TutorialBoardState::nextTutorialState()
{
	nextState++;
}

void TutorialBoardState::setBoard()
{
	TuVieja("\nEntering in LuisState");

	TuVieja(sdlutils().dialogues().at("El Xungo del Barrio").Convo(0).Node(3).Text());

	Factory* factory = new Factory();
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
	MatchManager* matchManagerComponent = matchManager->addComponent<MatchManager>(4, 4, Turns::J1, boardManagerComponent);


	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(boardManagerComponent);

	// Factoría de cartas. Con ella generamos la mano inicial
	ecs::entity_t deckPlayer1 = factory->createDeck();
	ecs::entity_t deckPlayer2 = factory->createDeckJ2();


	// UI 
	ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(100, 500);
	ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(600, 200, 200, 180);
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(170, 265);

	ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);

	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(700, 350, { 102, 255, 255, 255 });
	ecs::entity_t visual_ScoreCounterJ2 = factory->createVisual_ScoreCounter(700, 225, { 255, 102, 255, 255 });

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
	sdlutils().soundEffects().at("battletheme").play(-1);
	sdlutils().soundEffects().at("battletheme").setChannelVolume(30);


	#pragma region Seccion IA

	//crear la entidad y añadirle el componente
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
	//npc->getComponent<Transform>()->getRelativeScale().set(info.getScale().getX(), info.getScale().getY());
	Vector2D pos{ 200, 200 };
	base->getComponent<Transform>()->setGlobalPos(pos);
	base->setLayer(2);
}

void TutorialBoardState::createPopUp(float x, float y, std::string popup)
{
	TuVieja("Creando PopUp...");

	JsonData::DialogueData dialogue = sdlutils().dialogues().at(popup);
	int conv = 0;
	int node = 0;

	// crear dialogo del FACTORY de dialogos
	//// Mirar comentario en el interior de la función
	factory->createDialogue(dialogue.NPCName(), conv, node,
		{ x, y },//POS
		{ 100,100 }, //SIZE (poli: no cambia nada?¿)	// Luis: Dentro de createDialogue, size depende del tamaó del sprite, y no es parametrizable
		5, 10, base,
		3, dialogue.Convo(conv).isAuto(),  //LAYER
		"8bit_size_20",	//mirar el JSON para cambiar el tamanio de texto
		SDL_Color({ 0, 0, 0, 255 }),
		220, //wrap length
		Text::BoxPivotPoint::LeftTop,
		Text::TextAlignment::Left);
}

void TutorialBoardState::setINIT()
{

	TuVieja("Setting INIT");

	createPopUp(200, 200, "Board Tutorial");

}

void TutorialBoardState::setCARD()
{
}
