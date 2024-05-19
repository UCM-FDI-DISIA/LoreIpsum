#include <../pchs/pch.h>

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

#include "../components/managers/IA_manager.h"

#include "../components/managers/Manager.h"
#include "../GameStateMachine.h"
#include "../components/managers/PlayerCardsManager.h"
#include "game/components/Card.h"
#include "game/components/KeyComponent.h"

LuisState::LuisState() :
	GameState(),
	key_(nullptr),
	keyTr_(nullptr),
	moveKey_(false)
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

	if (moveKey_)
	{
		Vector2D newPos = keyTr_->getGlobalPos();
		if(newPos.getX() >= 100) {
			newPos = newPos - Vector2D(10, 0);
			keyTr_->setGlobalPos(newPos);
		}
	}
	else
	{
		Vector2D newPos = keyTr_->getGlobalPos();
		if(newPos.getX() <= 800)
		{
			newPos = newPos + Vector2D(10, 0);
			keyTr_->setGlobalPos(newPos);
		}
	}

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

	TuVieja(sdlutils().dialogues().at("El Xungo del Barrio").Convo(0).Node(3).Text());

	factory = new Factory();
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
	MatchManager* matchManagerComponent = matchManager->addComponent<MatchManager>(4, 4, Turns::J1, boardManagerComponent, j2_);


	// Drag Manager se encarga de gestionar el drag de todas las cartas
	ecs::entity_t dragManager = Instantiate();
	dragManager->addComponent<DragManager>();
	dragManager->getComponent<DragManager>()->setBoardManager(boardManagerComponent);
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::DRAG_MANAGER, dragManager);

	// Factoría de cartas. Con ella generamos la mano inicial
	ecs::entity_t deckPlayer1 = factory->createDeck();
	for (const auto c : deckPlayer1->getComponent<DeckComponent>()->getDeck())
		colliders_.push_back(c->getEntity()->getComponent<BoxCollider>());
	colliders_.push_back(deckPlayer1->getComponent<BoxCollider>());

	ecs::entity_t deckPlayer2 = factory->createDeckJ2(j2_);

	// Leyenda
	/*for (int i = 0; i < 6; ++i)
	{
		addKey();
	}*/
	key_ = Instantiate(Vector2D(800, 50));
	key_->setLayer(200);
	key_->getComponent<Transform>()->setGlobalScale(0.5, 0.5);
	key_->addComponent<SpriteRenderer>("key");
	key_->addComponent<KeyComponent>(getKeys());
	keyTr_ = key_->getComponent<Transform>();






	/// UI ///
	factory->createVisual_BackgroundFullImage();
	/// PUNTOS DE ACCION
	ecs::entity_t visual_ActionPointsJ1 = factory->createVisual_ActionPointsCounter(95, 280);
	//ecs::entity_t visual_ActionPointsJ2 = factory->createVisual_ActionPointsCounter(100, 100);

	/// BOTON END TURN
	ecs::entity_t visual_EndTurnButton = factory->createVisual_EndTurnButton(170, 250);
	colliders_.push_back(visual_EndTurnButton->getComponent<BoxCollider>());

	/// LEYENDA
	ecs::entity_t visual_KeyButton = factory->createVisual_KeyButton(720, 400);
	visual_KeyButton->getComponent<Transform>()->addParent(keyTr_);
	keyTr_->increaseLayer(key_->getLayer());

	/// TURNO Y SCORE
	ecs::entity_t visual_BoardInfoBG = factory->createVisual_BackgroundBlackBox(560, 170, 200, 180);
	//ecs::entity_t visual_PlayerTurnIndicator = factory->createVisual_PlayerTurnIndicator(700, 325);
	ecs::entity_t visual_ScoreCounterJ2 = factory->createVisual_ScoreCounter(680, 233, Colors::MORADO_BERENJENA);
	ecs::entity_t visual_ScoreCounterJ1 = factory->createVisual_ScoreCounter(680, 313, Colors::MIDNIGHT_LIGHT);










	// Enlazado de la UI con los scripts que la controlan
	//matchManagerComponent->setActualTurnVisual(visual_PlayerTurnIndicator);
	matchManagerComponent->setActionPointsVisualJ1(visual_ActionPointsJ1);
	//matchManagerComponent->setActionPointsVisualJ2(visual_ActionPointsJ2);
	matchManagerComponent->updateVisuals();

	boardManagerComponent->setScoreVisualJ1(visual_ScoreCounterJ1);
	boardManagerComponent->setScoreVisualJ2(visual_ScoreCounterJ2);
	boardManagerComponent->updateVisuals();


	// Seteamos la mano de J1 en el matchManager
	matchManagerComponent->SetHandComponent(deckPlayer1->getComponent<PlayerCardsManager>()->getHand());



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

void LuisState::onExit()
{
	TuVieja("\nExit LuisState");

	sdlutils().soundEffects().at("battletheme").pauseChannel();


	delete factory;

	GameStateMachine::instance()->getMngr()->Free();


}

void LuisState::setKey()
{
	moveKey_ = !moveKey_;
	if (moveKey_)
	{
		for (const auto b : colliders_)
			b->setPosOffset(Vector2D(1000, 1000));
	}
	else
	{
		for (const auto b : colliders_)
			b->setPosOffset(Vector2D(0, 0));
	}
}

void LuisState::setJ2(std::string rival)
{
	j2_ = rival;
}
