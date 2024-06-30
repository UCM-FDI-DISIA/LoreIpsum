#include <../pchs/pch.h>

#include "SolitaireQuestion.h"
#include "../components/managers/Manager.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"
#include "../components/Button.h"

// Factorias:
#include "../factories/NPCFactory_V0.h"
#include "game/components/Clickable.h"

SolitaireQuestion::SolitaireQuestion()
{

}

void SolitaireQuestion::update()
{
	GameState::update();

}

void SolitaireQuestion::render() const
{
	GameState::render();

}

void SolitaireQuestion::refresh()
{
	GameState::refresh();

}

void SolitaireQuestion::onEnter()
{
	//creacion del fondo
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("greenTable");
	fondo->getComponent<Transform>()->setGlobalScale(1.0f, 1.0f);
	fondo->setLayer(0);



	ecs::entity_t betText = Instantiate();
	betText->addComponent<Transform>();
	betText->addComponent<BoxCollider>();
	betText->getComponent<Transform>()->setGlobalPos(100, 100);
	betText->addComponent<SpriteRenderer>("betText");
	betText->getComponent<Transform>()->setGlobalScale(1.0f, 1.0f);
	betText->getComponent<Transform>()->setGlobalPos(200, 200);
	betText->setLayer(4);


	ecs::entity_t yes = Instantiate();
	yes->addComponent<Transform>()->addParent(betText->getComponent<Transform>());
	yes->addComponent<SpriteRenderer>("yes");
	yes->addComponent<BoxCollider>();
	yes->addComponent<Button>();
	yes->getComponent<Button>()->connectToButton([this] {});
	yes->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(33); });
	yes->getComponent<Transform>()->setGlobalScale(0.6f, 0.5f);
	yes->getComponent<Transform>()->setRelativePos(20, 85);
	//yes->getComponent<Transform>()->setGlobalPos(200, 200);
	yes->setLayer(5);

	ecs::entity_t no = Instantiate();
	no->addComponent<Transform>()->addParent(betText->getComponent<Transform>());
	no->addComponent<SpriteRenderer>("no");
	no->addComponent<BoxCollider>();
	no->getComponent<BoxCollider>();
	no->addComponent<Button>();
	no->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(32); });
	no->getComponent<Transform>()->setGlobalScale(0.9f, 0.7f);
	no->getComponent<Transform>()->setRelativePos(130, 85);
	no->setLayer(5);


}

void SolitaireQuestion::onExit()
{
	std::cout << "\nEXIT SOLITAIRE.";

	saveData();

	GameStateMachine::instance()->getMngr()->Free();

}