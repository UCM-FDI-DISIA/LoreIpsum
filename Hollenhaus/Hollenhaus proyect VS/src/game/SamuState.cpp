#include "SamuState.h"

#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"
#include "Entity.h"
#include "Manager.h"
#include "..\sdlutils\InputHandler.h"

#include "CardFactory_v0.h"

#include "Factory.h"

#include "BoardFactory_v0.h"

#include "MatchManager.h"

#include "BoardManager.h"
#include "TextComponent.h"
#include "MatchManager.h"
#include "EndTurnButton.h"

SamuState::SamuState() : GameState() {

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

	board->getComponent<BoardManager>()->updateScore();	// Esto puede ser un problema de performance

	//std::cout << "Player 1 points: " << board->getComponent<BoardManager>()->getPlayer1Points() << std::endl;
	//std::cout << "Player 2 points: " << board->getComponent<BoardManager>()->getPlayer2Points() << std::endl;
	#if _DEBUG
	std::cout << board->getComponent<BoardManager>()->getPlayer1Points() << std::endl;
	#endif
}

void SamuState::render() const
{
	GameState::render();
}

void SamuState::onEnter()
{
	TuVieja("\nEntering in SamuState");

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, MatchManager::TurnState::TurnJ1);

	// Factoría del tablero. Generamos el tablero de juego.
	boardFact = new BoardFactory(4, 4);
	board = boardFact->createBoard();

	// Factoría de cartas. Con ella generamos la mano inicial
	cardFact = new CardFactory_v0();
	cardFact->createHand();

	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	// Imágen de fondo
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.42, 0.56);
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

void SamuState::onExit() 
{
	TuVieja("\nExit SamuState");
	GameStateMachine::instance()->getMngr()->Free();
}
