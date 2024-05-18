#include <../pchs/pch.h>

#include "MatchOverState.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"
#include "../Data.h"
#include "../components/NPC.h"
#include "game/components/Button.h"
#include "game/components/Clickable.h"

MatchOverState::MatchOverState()
{
	TuVieja("Loading MatchOverState");
}

void MatchOverState::update()
{
	GameState::update();
}

void MatchOverState::render() const
{
	GameState::render();
}

void MatchOverState::refresh()
{
	GameState::refresh();
}

void MatchOverState::onEnter()
{
	std::cout << "\nENTER MATCHOVER.\n";

	//------Boton para volver:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	if (j2_ == "8") {
		exit->addComponent<Button>();
		exit->getComponent<Button>()->connectToButton([this]
		{
			GameStateMachine::instance()->setState(GameStates::ENDGAME);
		});
	}
	else
	{
		exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	}
	exit->setLayer(1);
	exit->addComponent<Clickable>("boton_flecha", true);

	setWindow(data->getWinner());
}

void MatchOverState::onExit()
{
	std::cout << "\nEXIT MATCHOVER.\n";
	GameStateMachine::instance()->getMngr()->Free();
}

void MatchOverState::setWindow(int lastWinner) {

	// Cual es el ultimo ganador de la partida?
	switch (lastWinner)
	{
	case 1: // Empate:
		_background = "rice";
		_text = "TIE :(";
		break;
	case 2: // Jugador1:
		_background = "fantasma";
		_text = "JUGADOR 1!";
		break;
	case 3: // Jugador2:
		_background = "logo_hollen";
		_text = "JUGADOR 2!";
		break;
	default:
		_background = "board5";
		_text = "NADIE?";
		break;
	}

	// ----- Imagen de fondo ---- 
	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->addComponent<SpriteRenderer>(_background);
	background->getComponent<Transform>()->setGlobalScale(0.5f, 0.5f);
	//background->getComponent<Transform>()->getGlobalScale().set(0.5f, 0.5f);
	background->setLayer(0);

	// ---- Texto ----
	ecs::entity_t matchOverText = Instantiate(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2));
	matchOverText->addComponent<TextComponent>("¡GANADOR: " + _text, Fonts::GROTESK_40, SDL_Color({ 255, 255, 255, 255 }), 500, Text::CenterCenter, Text::Center);
	matchOverText->setLayer(1);

	// ---- Resetea el ganador a nulo al salir del estado ----
	data->setWinner(0);
}

void MatchOverState::setJ2(std::string rival)
{
	j2_ = rival;
}
