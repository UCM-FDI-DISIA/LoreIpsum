#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "checkMazeMenuState.h"

CheckMazeMenuState::CheckMazeMenuState()
{
	TuVieja("Loading checkMazeMenuState");
}

CheckMazeMenuState::~CheckMazeMenuState()
{
}

void CheckMazeMenuState::refresh()
{
	GameState::refresh();
}

void CheckMazeMenuState::update()
{
	GameState::update();
}

void CheckMazeMenuState::render() const
{
	GameState::render();
}

void CheckMazeMenuState::onEnter()
{
	std::cout << "\nENTER CHECK MAZE\n";
}

void CheckMazeMenuState::onExit()
{
	std::cout << "\nEXIT CHECK MAZE\n";
}
