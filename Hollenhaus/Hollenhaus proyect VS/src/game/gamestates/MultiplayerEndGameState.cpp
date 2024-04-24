#include <../pchs/pch.h>
#include "MultiplayerEndGameState.h"

#include "../components/NPC.h"
#include "../components/Button.h"
#include "../components/basics/TextComponent.h"
#include "../components/multiplayer/NetEndGame.h"
#include "../Data.h"


MultiplayerEndGameState::MultiplayerEndGameState()
{
	TuVieja("Loading MultiplayerEndGameState");
}

MultiplayerEndGameState::~MultiplayerEndGameState()
{
}

void MultiplayerEndGameState::onEnter()
{
	TuVieja("ENTER MultiplayerEndGameState");


	auto netMn = Instantiate();

	auto netEndGame = netMn->addComponent<NetEndGame>();

	//------Boton para volver:
	auto playAgainButton = Instantiate(Vector2D(sdlutils().width() / 2, 230));
	auto playAgainText = playAgainButton->addComponent<TextComponent>("Jugar Otra Vez", "8bit_size_32",
	                                                                  SDL_Color({255, 255, 255, 255}), 150,
	                                                                  Text::BoxPivotPoint::CenterCenter,
	                                                                  Text::TextAlignment::Center);
	playAgainButton->addComponent<BoxCollider>();
	playAgainButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 80));
	playAgainButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -40));
	playAgainButton->addComponent<Button>();
	//conectar la funcion del netEndGame
	playAgainButton->getComponent<Button>()->connectToButton([this, netEndGame] { netEndGame->playAgain(); });
	//conectar swapColor
	playAgainButton->getComponent<Button>()->connectToButton(
		[this, netEndGame, playAgainText]
		{
			swapColor(playAgainText, netEndGame->getPlayAgainSelected());
		});
	playAgainButton->setLayer(1);

	//------Boton para cambiar mazo:
	auto changeMazeButton = Instantiate(Vector2D(sdlutils().width() / 2, 330));
	auto changeMazeText = changeMazeButton->addComponent<TextComponent>("Cambiar Mazo", "8bit_size_32",
	                                                                    SDL_Color({255, 255, 255, 255}), 150,
	                                                                    Text::BoxPivotPoint::CenterCenter,
	                                                                    Text::TextAlignment::Center);
	changeMazeButton->addComponent<BoxCollider>();
	changeMazeButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 80));
	changeMazeButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -40));
	changeMazeButton->addComponent<Button>();

	//conectar la funcion del netEndGame
	changeMazeButton->getComponent<Button>()->connectToButton([this, netEndGame] { netEndGame->changeMaze(); });
	//conectar swapColor
	changeMazeButton->getComponent<Button>()->connectToButton(
		[this, netEndGame, changeMazeText]
		{
			swapColor(changeMazeText, netEndGame->getChangeMazeSelected());
		});

	changeMazeButton->setLayer(1);


	//------Boton para salir
	auto exitButton = Instantiate(Vector2D(sdlutils().width() / 2, 430));
	exitButton->addComponent<TextComponent>("Salir", "8bit_size_32", SDL_Color({255, 255, 255, 255}), 150,
	                                        Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	exitButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	exitButton->addComponent<Button>();
	//conectar la funcion del netEndGame
	exitButton->getComponent<Button>()->connectToButton([this, netEndGame] { netEndGame->exit(); });
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
	matchOverText->addComponent<TextComponent>("¡GANADOR: " + _text, "8bit_size_40", SDL_Color({255, 255, 255, 255}),
	                                           500, Text::CenterCenter, Text::Center);
	matchOverText->setLayer(1);

	// ---- Resetea el ganador a nulo al salir del estado ----
	data->setWinner(0);
}

//cambia el color del texto del textComponent entre verde y blanco
void MultiplayerEndGameState::swapColor(TextComponent* tc, bool b)
{
	//color verde si seleccionado, blanco sino
	tc->setColor(b ? SDL_Color({0, 255, 0, 255}) : SDL_Color({255, 255, 255, 255}));
}
