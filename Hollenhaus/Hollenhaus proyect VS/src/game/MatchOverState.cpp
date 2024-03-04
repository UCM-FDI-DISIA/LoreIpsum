#include "MatchOverState.h"
#include "ShopState.h"
#include "Manager.h"
#include "TextComponent.h"

MatchOverState::MatchOverState()
{
	std::cout << "\nLoading ShopState.";
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
	exit->addComponent<SpriteRenderer>("boton");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	exit->setLayer(1);

	//setWindow(GameStateMachine().getData()->getWinner());
}

void MatchOverState::onExit()
{
	std::cout << "\nEXIT MATCHOVER.\n";
	GameStateMachine::instance()->getMngr()->Free();
}

void MatchOverState::setWindow(int lastWinner) {
	switch (lastWinner)
	{
	case 1: // Empate:
		background = "rice";
		text = "TIE :(";
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
		break;
	}

	// ----- Imagen de fondo ---- 
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>(background);
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

	// ---- Texto de la tienda ----
	ecs::entity_t shopText = Instantiate(Vector2D(400, 30));
	shopText->addComponent<TextComponent>("¡GANADOR:" + text, "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 350, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);
	shopText->setLayer(1);

	// ---- Resetea el ganador a nulo ----
	//GameStateMachine().getData()->setWinner(0);
}
