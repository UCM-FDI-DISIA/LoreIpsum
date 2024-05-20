#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "checkMazeMenuState.h"
#include "../components/NPC.h"
#include "game/Data.h"
#include "game/components/Clickable.h"
#include "../components/basics/TextComponent.h"


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

	auto tituloText = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 100));
	tituloText->addComponent<TextComponent>("MAZO ACTUAL", Fonts::GROTESK_32, Colors::PEARL_HOLLENHAUS, 400, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	tituloText->setLayer(1);

	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(100, 100);
	fondo->setLayer(0);

	//// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GameStates::PAUSEMENU);
	exit->setLayer(5);
	exit->addComponent<Clickable>("boton_flecha", true);

	ShowMaze();
}

void CheckMazeMenuState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();
}

void CheckMazeMenuState::ShowMaze()
{
	mazeAux = GameStateMachine::instance()->getCurrentState()->getMaze();
	int cardsPos; 
	int i = 2;

	for (auto e : mazeAux) {

		if (e != -1)
		{
			if(i <= 9) { cardsPos = 100; }
			else if(i >= 10 && i <= 17)
			{
				if(i == 10)
				{
					i = 2;
				}
				cardsPos = 200;
			}
			else if(i >= 18)
			{
				if (i == 18)
				{
					i = 2;
				}
				cardsPos = 300;
			}

			ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
			(e, Vector2D(i * 70, cardsPos));
		}

		i++;
	}
}