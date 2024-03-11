#include "pch.h"

#include "LuisState.h"
#include <SDL.h>

#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"

#include "Factory.h"
#include "CardFactory_v0.h"
#include "CardFactory_v1.h"
#include "BoardFactory_v0.h"
#include "MatchStateUIFactory_v0.h"

#include "MatchManager.h"
#include "BoardManager.h"
#include "TextComponent.h"
#include "MatchManager.h"
#include "EndTurnButton.h"
#include "NPC.h"

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

	// Factor�a del tablero. Generamos el tablero de juego.
	ecs::entity_t board = factory->createBoard();

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, 4, MatchManager::TurnState::TurnJ1, board->getComponent<BoardManager>());

	// Factor�a de cartas. Con ella generamos la mano inicial
	factory->createDeck();
	factory->createDeckJ2();

	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());


	// UI 
	ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(100, 500);
	ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(600, 200, 200, 180);
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(200, 265);

	ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);

	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(700, 350, {102, 255, 255, 255});
	ecs::entity_t visual_ScoreCounterJ2 = factory->createVisual_ScoreCounter(700, 225, { 255, 102, 255, 255 });

	// Im�gen de fondo
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.555, 0.555);
	background->addComponent<SpriteRenderer>("board");
	//background->setLayer(-1);


	//// Creaci�n del bot�n de J1 (ahora general) para acabar su turno (debug por consola)
	//ecs::entity_t endTurnButtonJ1 = Instantiate(Vector2D(sdlutils().width() / 4, sdlutils().height() / 2 - 35));
	//endTurnButtonJ1->getComponent<Transform>()->getGlobalScale().set(1.2, 1.2);
	//endTurnButtonJ1->addComponent<SpriteRenderer>("EndTurnButton");
	//endTurnButtonJ1->addComponent<BoxCollider>();
	//endTurnButtonJ1->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ1);

	// Creaci�n del bot�n de J2 para acabar su turno (debug por consola)
	/*ecs::entity_t endTurnButtonJ2 = Instantiate(Vector2D(60, 100));
	endTurnButtonJ2->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ2->addComponent<BoxCollider>();
	endTurnButtonJ2->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ2);*/


	//ecs::entity_t puntosDeAccionText = Instantiate(Vector2D(100, 300));
	//puntosDeAccionText->addComponent<TextComponent>("Puntos de acci�n:", "8bit_16pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	// incicia la cancion en bucle
	//sdl.musics().at("tryTheme").play();
	sdlutils().soundEffects().at("battletheme").play(-1);
	sdlutils().soundEffects().at("battletheme").setChannelVolume(30);
}

void LuisState::onExit()
{
	TuVieja("\nExit SamuState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();
}
