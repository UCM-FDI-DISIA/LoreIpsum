#include "pch.h"
#include "NievesState.h"

#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"

#include "Manager.h"
#include "..\sdlutils\InputHandler.h"

#include "CardFactory_v0.h"
#include "CardFactory_v1.h"

#include "Factory.h"

#include "BoardFactory_v0.h"

#include "MatchManager.h"

#include "BoardManager.h"
#include "TextComponent.h"
#include "MatchManager.h"
#include "EndTurnButton.h"

NievesState::NievesState() : GameState() {

	TuVieja("Loading NievesState");
}

NievesState::~NievesState()
{

}
//cleon: si est� vac�o se llama directamente al padre
void NievesState::refresh()
{
	GameState::refresh();
}

void NievesState::update()
{

	//system("CLS");


	GameState::update();

	board->getComponent<BoardManager>()->updateScore();	// Esto puede ser un problema de performance

#if _DEBUG
	//std::cout << board->getComponent<BoardManager>()->getPlayer1Points() << std::endl;
	std::cout << GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getActualActionPointsJ1() << std::endl;
#endif
}

void NievesState::render() const
{
	GameState::render();
}

void NievesState::onEnter()
{
	TuVieja("\nEntering in NievesState");


	Factory* factory = new Factory();
	factory->SetFactories((BoardFactory*)new  BoardFactory_v0(4), (CardFactory*) new CardFactory_v1());

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, MatchManager::TurnState::TurnJ1);

	// Factoría del tablero. Generamos el tablero de juego.
	board = factory->createBoard();

	matchManager->getComponent<MatchManager>()->setBoardManager(board->getComponent<BoardManager>());

	// Factoría de cartas. Con ella generamos la mano inicial
	factory->createDeck();

	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	// Imágen de fondo
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.5, 0.5);
	background->addComponent<SpriteRenderer>("board");
	background->setLayer(-1);

	// Texto de prueba
	ecs::entity_t pruebaTxt = Instantiate(Vector2D(400, 50));
	pruebaTxt->addComponent<TextComponent>("Buenas tardes a los que ya han comido", "8bit_16pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	// Creación del botón de J1 para acabar su turno (debug por consola)
	ecs::entity_t endTurnButtonJ1 = Instantiate(Vector2D(60, 500));
	endTurnButtonJ1->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ1->addComponent<BoxCollider>();
	endTurnButtonJ1->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ1);

	// Creación del botón de J2 para acabar su turno (debug por consola)
	ecs::entity_t endTurnButtonJ2 = Instantiate(Vector2D(60, 100));
	endTurnButtonJ2->addComponent<SpriteRenderer>("EndTurnButton");
	endTurnButtonJ2->addComponent<BoxCollider>();
	endTurnButtonJ2->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ2);
}

void NievesState::onExit()
{
	TuVieja("\nExit NievesState");
	GameStateMachine::instance()->getMngr()->Free();
}
