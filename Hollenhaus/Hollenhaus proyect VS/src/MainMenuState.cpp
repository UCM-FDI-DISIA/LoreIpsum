#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* game) 
	: GameState(game)
{
	
}

void MainMenuState::Render() const {
	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	game->RenderClear();

	//render del background
	//game->getTexture(MAINMENU)->render();

	//render de los gameObjects
	GameState::Render();
}

void MainMenuState::PlayGame() {
	game->getGameStateMachine()->pushState(new PlayState(game));
}

void MainMenuState::Exit() {
	game->getGameStateMachine()->popState();
}

