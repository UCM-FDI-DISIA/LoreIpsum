#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "checkMazeMenuState.h"
#include "../components/NPC.h"
#include "game/Data.h"

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

		//std::list<int>::iterator findIter = std::find(mazeAux.begin(), mazeAux.end(), e);
		if (e != -1)
		{
			ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
			(e, Vector2D(i * 70, 100));
		}

		i++;
	}

	//for (int i = 0; i < GameStateMachine::instance()->getCurrentState()->getMaze().size(); i++)
	//{

	//	// si la carta esta desbloqueada
		//if (*findIter != -1)
		//{
		//	// la crea
		//	ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
		//	(*findIter, Vector2D(i, 100));
		//}
	//}
}