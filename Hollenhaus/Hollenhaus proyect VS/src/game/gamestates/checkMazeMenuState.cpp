#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "checkMazeMenuState.h"
#include "../components/NPC.h"
#include "game/Data.h"
#include "game/components/Clickable.h"

CheckMazeMenuState::CheckMazeMenuState()
{
	TuVieja("Loading checkMazeMenuState");
}

CheckMazeMenuState::~CheckMazeMenuState()
{
}

void CheckMazeMenuState::refresh()
{
	GameState::refresh();
}

void CheckMazeMenuState::update()
{
	GameState::update();
}

void CheckMazeMenuState::render() const
{
	GameState::render();
}

void CheckMazeMenuState::onEnter()
{
	std::cout << "\nENTER CHECK MAZE\n";

	//// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(17);
	exit->setLayer(5);
	exit->addComponent<Clickable>("boton_flecha", true);

	ShowMaze();
}

void CheckMazeMenuState::onExit()
{
	std::cout << "\nEXIT CHECK MAZE\n";
	GameStateMachine::instance()->getMngr()->Free();
}

void CheckMazeMenuState::ShowMaze()
{
	mazeAux = GameStateMachine::instance()->getCurrentState()->getMaze();

	int i = 1;
	for (auto e : mazeAux) {

		if (e != -1)
		{
			ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
			(e, Vector2D(i * 70, 100));
		}

		i++;
	}
}