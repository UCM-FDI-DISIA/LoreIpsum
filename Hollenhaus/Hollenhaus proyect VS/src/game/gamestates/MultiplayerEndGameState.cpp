#include "pch.h"
#include "MultiplayerEndGameState.h"

#include "../components/NPC.h"
#include "../components/Button.h"
#include "../components/basics/TextComponent.h"
#include "../Data.h"


MultiplayerEndGameState::MultiplayerEndGameState()
{
	TuVieja("Loading MultiplayerEndGameState");
}

MultiplayerEndGameState::~MultiplayerEndGameState()
{
}

void MultiplayerEndGameState::refresh()
{
	GameState::refresh();
}

void MultiplayerEndGameState::update()
{
	GameState::update();
}

void MultiplayerEndGameState::render() const
{
	GameState::render();
}

void MultiplayerEndGameState::onEnter()
{
	TuVieja("ENTER MultiplayerEndGameState");


	//------Boton para volver:
	auto playAgainButton = Instantiate(Vector2D(sdlutils().width()/2, 230));
	playAgainButton->addComponent<TextComponent>("Jugar Otra Vez", "8bit_size_32", SDL_Color({ 255, 255,255 ,255 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	playAgainButton->addComponent<BoxCollider>();
	playAgainButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 80));
	playAgainButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -40));
	playAgainButton->addComponent<Button>();
	playAgainButton->getComponent<Button>()->connectToButton([this] {playAgain(); });
	playAgainButton->setLayer(1);

	//------Boton para cambiar mazo:
	auto changeMazeButton = Instantiate(Vector2D(sdlutils().width() / 2, 330));
	changeMazeButton->addComponent<TextComponent>("Cambiar Mazo", "8bit_size_32", SDL_Color({ 255, 255,255 ,255 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	changeMazeButton->addComponent<BoxCollider>();
	changeMazeButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 80));
	changeMazeButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -40));
	changeMazeButton->addComponent<Button>();
	changeMazeButton->getComponent<Button>()->connectToButton([this] {changeMaze(); });
	changeMazeButton->setLayer(1);


	//------Boton para salir
	auto exitButton = Instantiate(Vector2D(sdlutils().width() / 2, 430));
	exitButton->addComponent<TextComponent>("Salir", "8bit_size_32", SDL_Color({ 255, 255,255 ,255 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	exitButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	exitButton->addComponent<Button>();
	exitButton->getComponent<Button>()->connectToButton([this] {exit(); });
	exitButton->setLayer(1);



	setWindow(data->getWinner());
}

void MultiplayerEndGameState::onExit()
{
	TuVieja("EXIT MultiplayerEndGameState");
	mngr().Free();


}

void MultiplayerEndGameState::setWindow(int lastWinner)
{
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
		_background = "npc";
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
	ecs::entity_t matchOverText = Instantiate(Vector2D(sdlutils().width() / 2, 100));
	matchOverText->addComponent<TextComponent>("¡GANADOR: " + _text, "8bit_size_40", SDL_Color({ 255, 255, 255, 255 }), 500, Text::CenterCenter, Text::Center);
	matchOverText->setLayer(1);

	// ---- Resetea el ganador a nulo al salir del estado ----
	data->setWinner(0);
}

void MultiplayerEndGameState::playAgain()
{
	TuVieja("Boton de jugar otra vez pulsado");

	//ir al menu de MultiplayerGame(sin cerrar el socket del rival)
	//se cierra el socketSet

}

void MultiplayerEndGameState::changeMaze()
{
	TuVieja("Boton de cambiar mazo pulsado");

	//ir al menu de MultiplayerPreGame(sin cerrar el socket del rival)
	//se cierra el socket set


}

void MultiplayerEndGameState::exit()
{
	TuVieja("Boton de salir pulsado");

	//cerrar socket del rival y el socketSet


	//ir al menu principal
	GameStateMachine::instance()->setState(GameStates::MAINMENU);
}
