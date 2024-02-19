#include "BoardState.h"
#include "../sdlutils/InputHandler.h"
#include <algorithm>

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
	inputCard();
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

void BoardState::inputCard()
{
	render();
	int x, y;
	int cost, value;
	int player;
	std::string skill;

	std::cout << "Coordenada X: ";
	std::cin >> x;
	std::cout << "Coordenada Y: ";
	std::cin >> y;
	std::cout << "Coste: ";
	std::cin >> cost;
	std::cout << "Valor: ";
	std::cin >> value;
	std::cout << "Jugador (1 -> jugador 1, 2 -> jugador 2): ";
	std::cin >> player;
	std::cout << "Habilidad: ";
	std::cin >> skill;

	Owner owner = NONE;
	player = std::clamp(player, 0, 2);
	switch (player)
	{
	case 1: owner = PLAYER1; break;
	case 2: owner = PLAYER2; break;
	default: break;
	}

	x = std::clamp(x, 0, board->getWidth() - 1);
	y = std::clamp(y, 0, board->getHeight() - 1);

	board->setCard(x, y, new Card(cost, value, skill), owner);
}
