#include "BoardState.h"
#include "../sdlutils/InputHandler.h"
#include <algorithm>
#include "Manager.h"
#include "TextComponent.h"

BoardState::BoardState()
{
	board = new Board(4);
	matchManager = new MatchManager();
	effectCollection = new EffectCollection();

}

BoardState::~BoardState()
{
	delete board;
	delete matchManager;
	delete effectCollection;
	delete cardPH;
}

void BoardState::update()
{
	inputCard();
}

void BoardState::render() const
{
	// limpia la consola
	system("CLS");

	std::cout << "PLAYER 1: " << matchManager->getPlayer1Points()
			  << " PLAYER 2: " << matchManager->getPlayer2Points()
			  << "\n";
	board->paintBoard();
}

void BoardState::refresh()
{
}

void BoardState::inputCard()
{
	int x, y;
	int cost, value;
	int player = 0,
		blockint = 0;
	bool block = false;
	int typecard;
	std::string skill;
	std::string sprite = "yippieeee";

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
	std::cout << "Unblockeable: ";
	std::cin >> blockint;
	std::cout << "card (0 -> block, 1-> addcorner): ";
	std::cin >> typecard;

	CellData::Owner owner = CellData::NONE;
	player = std::clamp(player, 0, 2);
	switch (player)
	{
	case 1: owner = CellData::PLAYER1;
		break;
	case 2: owner = CellData::PLAYER2;
		break;
	default: break;
	}

	if (blockint == 1)
		block = true;

	x = std::clamp(x, 0, board->getSize() - 1);
	y = std::clamp(y, 0, board->getSize() - 1);

	cardPH = new Card(cost, value, sprite, block);
	int skillv = std::stoi(skill); // string a int

	if (typecard == 0) 
		cardPH->addCardEffect([this, x, y] {
				effectCollection->blockCard(board->getCell(x, y), CellData::Down);
		});
	else if (typecard == 1) 
		cardPH->addCardEffect([this, x, y, skillv] {
				effectCollection->addAdj(board->getCell(x, y), CellData::Down, skillv, false);
		});

	board->setCard(x, y, cardPH, owner);
	matchManager->updateScore(); // actualiza el matchManager siempre que se ponga una carta
}
