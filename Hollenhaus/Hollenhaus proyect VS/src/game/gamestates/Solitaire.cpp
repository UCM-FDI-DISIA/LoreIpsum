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

#include <algorithm>    // std::random_shuffle

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

	/*
	ecs::entity_t betText = Instantiate();
	betText->addComponent<Transform>();
	betText->addComponent<BoxCollider>();
	betText->getComponent<Transform>()->setGlobalPos(100, 100);
	betText->addComponent<SpriteRenderer>("betText");
	betText->getComponent<Transform>()->setGlobalScale(1.0f, 1.0f);
	betText->setLayer(4);

	ecs::entity_t yes = Instantiate();
	yes->addComponent<Transform>()->addParent(betText->getComponent<Transform>());
	yes->addComponent<BoxCollider>();
	//yes->getComponent<BoxCollider>()->setSize(Vector2D(45,45)); ajustar esto somehow
	yes->addComponent<SpriteRenderer>("yes");
	yes->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	yes->getComponent<Transform>()->setRelativePos(100, 100);
	yes->setLayer(5);

	ecs::entity_t no = Instantiate();
	no->addComponent<Transform>()->addParent(betText->getComponent<Transform>());
	no->addComponent<BoxCollider>();
	//no->getComponent<BoxCollider>()->setSize(Vector2D(45,45)); ajustar esto somehow
	no->addComponent<SpriteRenderer>("no");
	no->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	no->getComponent<Transform>()->setRelativePos(150, 150);
	no->setLayer(5);
	*/

	//creacion de las cartas

	for (int i = 0; i < 37; i++) {
		// hay 37 cartas bocabajo a la izquierda
	}

	//y quince cartas en el medio 
	std::vector<int> indices{

		28,
		18,1,
		9,32,43,
		50,18,3,7,
		29,33,51,3,34
	};

	std::vector<int> indicesAleatorios;

	for (int i = 0; i < 52; i++)
		indicesAleatorios.push_back(i);

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(indicesAleatorios.begin(), indicesAleatorios.end(),g);
	solCardFactory->createCardsBoard(indicesAleatorios);
	/*
	solCardFactory->CreateCard(5, SolCardComponent::clubs, true, Vector2D(15,10));
	solCardFactory->CreateCard(3, SolCardComponent::hearts, false, Vector2D(150, 10));
	solCardFactory->CreateCard(2, SolCardComponent::clubs, false, Vector2D(150, 30));
	solCardFactory->CreateCard(4, SolCardComponent::spades, false, Vector2D(250, 10));
	solCardFactory->CreateCard(12, SolCardComponent::diamonds, false, Vector2D(350, 10));
	solCardFactory->CreateCard(1, SolCardComponent::clubs, false, Vector2D(450, 10));
	solCardFactory->CreateCard(8, SolCardComponent::hearts, false, Vector2D(550, 10));
	*/

	//casillas de la derecha 
	solCardFactory->CreateCasillaDcha(2, Vector2D(695, 35));
	solCardFactory->CreateCasillaDcha(3, Vector2D(695, 175));
	solCardFactory->CreateCasillaDcha(1, Vector2D(695, 323));
	solCardFactory->CreateCasillaDcha(0, Vector2D(695, 465));

	ecs::entity_t dragManager = Instantiate();
	dragManager->addComponent<SolDragComponent>();
}

void Solitaire::onExit()
{
	delete solCardFactory;
}