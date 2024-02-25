#include "MainMenuState.h"

MainMenuState::MainMenuState()
	 
{
	
	std::cout << "\nLoading Menu";
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
	std::cout << "\nEnter menu\n";
}

void MainMenuState::onExit() const
{
	std::cout << "\nExit menu\n";
}

