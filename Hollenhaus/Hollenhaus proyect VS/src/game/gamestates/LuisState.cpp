#include "pch.h"
#include "LuisState.h"
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

LuisState::LuisState() : GameState()
{
	TuVieja("Loading LuisState");
}

LuisState::~LuisState()
{
}


void LuisState::refresh()
{
	GameState::refresh();
}

void LuisState::update()
{
	GameState::update();

#if _DEBUG
	//std::cout << sdlutils().dialogues().at("0").text()<< std::endl;
#endif
}

void LuisState::render() const
{
	GameState::render();
}

void LuisState::onEnter()
{
	TuVieja("\nEntering in LuisState");

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
	MatchManager* matchManagerComponent = matchManager->addComponent<MatchManager>(4, 4, MatchManager::TurnState::TurnJ1, boardManagerComponent);


	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(boardManagerComponent);

	// Factoría de cartas. Con ella generamos la mano inicial
	factory->createDeck();
	factory->createDeckJ2();


	// UI 
	ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(100, 500);
	ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(600, 200, 200, 180);
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(170, 265);

	ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);

	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(700, 350, {102, 255, 255, 255});
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
}

void LuisState::onExit()
{
	TuVieja("\nExit LuisState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();
}
