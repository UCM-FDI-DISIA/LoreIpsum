#include "SamuState.h"
#include <SDL.h>
#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"
#include "Entity.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"
#include "CardFactory_v0.h"
#include "CardFactory_v1.h"
#include "Factory.h"
#include "BoardFactory_v0.h"
#include "MatchManager.h"
#include "BoardManager.h"
#include "TextComponent.h"
#include "MatchManager.h"
#include "EndTurnButton.h"

SamuState::SamuState() : GameState()
{
	TuVieja("\nloading SAmuState");
}

SamuState::~SamuState()
{
}

//cleon: si est� vac�o se llama directamente al padre
void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	//system("CLS");


	GameState::update();

	//board->getComponent<BoardManager>()->updateScore(); // Esto puede ser un problema de performance // ahora está en el setcard


	// esto tambien deberia ejecutarse solo cuando se ponga una carta, no aqui
	int actionPointsValue = mngr().getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->
	                               getActualActionPoints();
	actionPointsVisualJ1->getComponent<TextComponent>()->setTxt(
		"Puntos de accion:\n\n" + std::to_string(actionPointsValue));

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

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, MatchManager::TurnState::TurnJ1);

	// Factoría del tablero. Generamos el tablero de juego.
	board = factory->createBoard();

	// Factoría de cartas. Con ella generamos la mano inicial
	factory->createDeck();

	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	// Imágen de fondo
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.555, 0.555);
	background->addComponent<SpriteRenderer>("board");
	background->setLayer(-1);


	// Creación del botón de J1 (ahora general) para acabar su turno (debug por consola)
	ecs::entity_t endTurnButtonJ1 = Instantiate(Vector2D(sdlutils().width()/4, sdlutils().height()/2 - 35));
	endTurnButtonJ1->getComponent<Transform>()->getGlobalScale().set(1.2, 1.2);
	endTurnButtonJ1->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ1->addComponent<BoxCollider>();
	endTurnButtonJ1->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ1);

	// Creación del botón de J2 para acabar su turno (debug por consola)
	/*ecs::entity_t endTurnButtonJ2 = Instantiate(Vector2D(60, 100));
	endTurnButtonJ2->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ2->addComponent<BoxCollider>();
	endTurnButtonJ2->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ2);*/

	// Puntos de acción restantes
	int actionPointsValue = mngr().getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->
	                               getActualActionPoints();
	actionPointsVisualJ1 = Instantiate(Vector2D(100, sdlutils().height() - 100));
	actionPointsVisualJ1->addComponent<TextComponent>("Puntos de accion:\n\n" + std::to_string(actionPointsValue),
	                                                "8bit_16pt", SDL_Color({255, 255, 0, 255}), 200,
	                                                TextComponent::BoxPivotPoint::CenterCenter,
	                                                TextComponent::TextAlignment::Center);

	actionPointsVisualJ2 = Instantiate(Vector2D(100, 100));
	actionPointsVisualJ2->addComponent<TextComponent>("Puntos de accion:\n\n" + std::to_string(actionPointsValue),
	                                                "8bit_16pt", SDL_Color({255, 255, 0, 255}), 200,
	                                                TextComponent::BoxPivotPoint::CenterCenter,
	                                                TextComponent::TextAlignment::Center);


	//ecs::entity_t puntosDeAccionText = Instantiate(Vector2D(100, 300));
	//puntosDeAccionText->addComponent<TextComponent>("Puntos de acción:", "8bit_16pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	// incicia la cancion en bucle
	//sdl.musics().at("tryTheme").play();
	sdlutils().soundEffects().at("battletheme").play(-1);
	sdlutils().soundEffects().at("battletheme").setChannelVolume(10);
}

void SamuState::onExit()
{
	TuVieja("\nExit SamuState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();
}
