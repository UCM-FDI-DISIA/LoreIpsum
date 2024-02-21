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

void MainMenuState::onEnter() const
{
	std::cout << "\nenter menu\n";
}

void MainMenuState::onExit() const
{
	std::cout << "\nexit menu\n";
}

