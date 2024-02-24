#include "BoardState.h"
#include "../sdlutils/InputHandler.h"
#include <algorithm>

BoardState::BoardState()
{
	board = new Board(4);
	matchManager = new MatchManager(board);
	collection = EffectCollection();
	
	std::cout << "board state";
}

BoardState::~BoardState()
{
	delete board;
	delete matchManager;
	delete cardPH;
}

void BoardState::update()
{
	//if (ih().isKeyDown(SDL_SCANCODE_RETURN))
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
	case 1: owner = PLAYER1;
		break;
	case 2: owner = PLAYER2;
		break;
	default: break;
	}

	x = std::clamp(x, 0, board->getSize() - 1);
	y = std::clamp(y, 0, board->getSize() - 1);



	cardPH = new Card(cost, value);
	int skillv = std::stoi(skill);


	// [] -> contexto para los corchetes del lambda, pasar no solo el this si no las 
	// variables que necesites para el metodo
	cardPH->addCardEffect( 
		[this, x, y, skillv]() {
			collection.addValueCenter(board->getCell(x, y), skillv);
		}
	);


	board->setCard(x, y, cardPH, owner);
	
	// actualiza el matchManager siempre que se ponga una carta
	matchManager->updateScore();
}
