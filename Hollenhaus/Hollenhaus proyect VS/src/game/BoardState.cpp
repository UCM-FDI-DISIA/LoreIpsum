#include "BoardState.h"

BoardState::BoardState() : GameState()
{


}

BoardState::~BoardState()
{


}

void BoardState::update()
{


}

void BoardState::render() const 
{



}

void BoardState::onEnter() const
{
	std::cout << "\nenter board\n";
}

void BoardState::onExit() const
{
	std::cout << "\nexit board\n";
}
