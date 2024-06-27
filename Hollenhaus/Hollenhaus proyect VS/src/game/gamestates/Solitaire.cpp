#include <../pchs/pch.h>

#include "Solitaire.h"
#include "../components/managers/Manager.h"
#include "../components/ShineComponent.h"
#include "../components/SolCardComponent.h"
#include "../components/SolDragComponent.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"
#include "../components/Button.h"
#include "../../sdlutils/RandomNumberGenerator.h"
#include "../SoundManager.h"

// Factorias:
#include "../factories/Factory.h"
#include "../factories/SolCardFactory.h"
#include "../factories/NPCFactory_V0.h"
#include "game/components/Clickable.h"



Solitaire::Solitaire()
{

}

void Solitaire::update()
{
	GameState::update();

}

void Solitaire::render() const
{
	GameState::render();

}

void Solitaire::refresh()
{
	GameState::refresh();

}

void Solitaire::onEnter()
{
	//crear la factory
	solCardFactory = new SolCardFactory();

	//creacion del fondo
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("greenTable");
	fondo->getComponent<Transform>()->setGlobalScale(1.0f, 1.0f);
	fondo->setLayer(0);

	//creacion de las cartas
	solCardFactory->CreateCard(2, SolCardComponent::clubs, true, Vector2D(10,10));
	solCardFactory->CreateCard(3, SolCardComponent::hearts, false, Vector2D(200, 10));
	solCardFactory->CreateCard(4, SolCardComponent::spades, false, Vector2D(280, 10));
	solCardFactory->CreateCard(12, SolCardComponent::diamonds, false, Vector2D(360, 10));
	solCardFactory->CreateCard(1, SolCardComponent::clubs, false, Vector2D(440, 10));
	solCardFactory->CreateCard(8, SolCardComponent::hearts, false, Vector2D(520, 10));

	ecs::entity_t dragManager = Instantiate();
	dragManager->addComponent<SolDragComponent>();
}

void Solitaire::onExit()
{
	delete solCardFactory;
}