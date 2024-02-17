#include "BoardState.h"

BoardState::BoardState()
{
	board = new Board();
	std::cout << "board state";

}

BoardState::~BoardState()
{
	delete board;

}

void BoardState::update()
{
	

	std::cin >> input;

	

}

void BoardState::render()
{
	// limpia la consola
	system("CLS");

	board->PaintBoard();

}

void BoardState::refresh()
{
}
