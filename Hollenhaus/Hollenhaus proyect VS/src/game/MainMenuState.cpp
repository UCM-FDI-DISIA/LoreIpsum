#include "MainMenuState.h"

MainMenuState::MainMenuState()
	 
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
