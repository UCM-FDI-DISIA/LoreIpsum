#include <../pchs/pch.h>


#include "SamuState.h"
#include <SDL.h>

#include "../components/Drag.h"
#include "../components/managers/CardStateManager.h"
#include "../components/managers/DragManager.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../factories/CardFactory_v0.h"
#include "../factories/CardFactory_v1.h"
#include "../factories/Factory.h"
#include "../factories/BoardFactory_v0.h"
#include "../components/managers/MatchManager.h"
#include "../components/managers/BoardManager.h"
#include "../components/basics/TextComponent.h"
#include "../components/managers/MatchManager.h"
#include "../components/EndTurnButton.h"
#include "../components/NPC.h"

SamuState::SamuState() : GameState()
{
	TuVieja("Loading SamuState");
}

SamuState::~SamuState()
{
}

//cleon: si esta vacio se llama directamente al padre
void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	GameState::update();

#if _DEBUG

#endif
}

void SamuState::render() const
{
	GameState::render();
}

void SamuState::onEnter()
{
	TuVieja("\nEntering in SamuState");

	auto factory = new Factory();
	factory->SetFactories(static_cast<BoardFactory*>(new BoardFactory_v0(4)),
	                      static_cast<CardFactory*>(new CardFactory_v1()));

	// Factoría del tablero. Generamos el tablero de juego.
	board = factory->createBoard();

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, 4, Turns::J1, board->getComponent<BoardManager>());

	// Factoría de cartas. Con ella generamos la mano inicial
	factory->createDeck();
	factory->createDeckJ2();

	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	// Imágen de fondo
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->setGlobalScale(0.555f, 0.555f);
	//background->getComponent<Transform>()->getGlobalScale().set(0.555, 0.555);
	background->addComponent<SpriteRenderer>("board");
	//background->setLayer(-1);


	// Creación del botón de J1 (ahora general) para acabar su turno (debug por consola)
	ecs::entity_t endTurnButtonJ1 = Instantiate(Vector2D(sdlutils().width() / 4, sdlutils().height() / 2 - 35));
	endTurnButtonJ1->getComponent<Transform>()->setGlobalScale(1.2f, 1.2f);
	//endTurnButtonJ1->getComponent<Transform>()->getGlobalScale().set(1.2, 1.2);
	endTurnButtonJ1->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ1->addComponent<BoxCollider>();
	endTurnButtonJ1->addComponent<EndTurnButton>(Turns::J1);

	// Creación del botón de J2 para acabar su turno (debug por consola)
	/*ecs::entity_t endTurnButtonJ2 = Instantiate(Vector2D(60, 100));
	endTurnButtonJ2->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ2->addComponent<BoxCollider>();
	endTurnButtonJ2->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ2);*/

	// incicia la cancion en bucle
	//sdl.musics().at("tryTheme").play();
	sdlutils().soundEffects().at("battletheme").play(-1);
	sdlutils().soundEffects().at("battletheme").setChannelVolume(30);
}

void SamuState::onExit()
{
	TuVieja("\nExit SamuState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();
}
