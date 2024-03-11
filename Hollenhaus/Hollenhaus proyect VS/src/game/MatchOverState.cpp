#include "pch.h"
#include "MatchOverState.h"
#include "ShopState.h"
#include "Manager.h"
#include "TextComponent.h"

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
	exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	exit->setLayer(1);

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
		background = "rice";
		text = "TIE :(!";
		break;
	case 2: // Jugador1:
		background = "mouse";
		text = "JUGADOR1!";
		break;
	case 3: // Jugador2:
		background = "npc";
		text = "JUGADOR2!";
		break;
	default:
		background = "board5";
		text = "NADIE?";
		break;
	}

	// ----- Imagen de fondo ---- 
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>(background);
	fondo->getComponent<Transform>()->getGlobalScale().set(0.5f, 0.5f);
	fondo->setLayer(0);

	// ---- Texto ----
	ecs::entity_t shopText = Instantiate(Vector2D(300, 250));
	shopText->addComponent<TextComponent>("¡GANADOR:" + text, "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 400, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	shopText->setLayer(1);

	// ---- Resetea el ganador a nulo al salir del estado ----
	data->setWinner(0);
}
