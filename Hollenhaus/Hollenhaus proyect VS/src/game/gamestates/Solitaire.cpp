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
	
	ecs::entity_t exitButton = Instantiate(Vector2D(20, 20));
	exitButton->addComponent<Transform>();
	exitButton->addComponent<SpriteRenderer>("boton_flecha");
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exitButton->addComponent<Button>();
	exitButton->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(32); addMoney(-50); });
	exitButton->addComponent<Clickable>("boton_flecha", true);
	exitButton->getComponent<Transform>()->setGlobalPos(10, 500);

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

	//casilla de la izquierda para apilar cartas
	solCardFactory->CreateCasillaIzqda(0, Vector2D(10, 130));


	ecs::entity_t dragManager = Instantiate();
	dragManager->addComponent<SolDragComponent>();

}

void Solitaire::onExit()
{
	std::cout << "\nEXIT SOLITAIRE.";

	saveData();

	GameStateMachine::instance()->getMngr()->Free();

	delete solCardFactory;
}