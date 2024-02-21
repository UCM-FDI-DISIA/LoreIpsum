#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* game)
	: GameState(game)
{
	onEnter();
}

void MainMenuState::update()
{
}

void MainMenuState::render() const 
{
}

void MainMenuState::refresh()
{
}

void MainMenuState::onEnter()
{
	std::cout << "menu";
}

bool MainMenuState::onExit()
{
	return false;
}
