#include "Board.h"

Board::Board()
{
	IniciaTablero();

}

void Board::PaintBoard()
{


}

std::string Board::GetCard(Card* card)
{
	std::string info = "[" + std::to_string(card->getValue()) + "/" 
						   + std::to_string(card->getCost()) + "/"
						   + getEffect(card) + "]";

	return info;
}

std::string Board::getEffect(Card* card)
{
	return "YIIPIEEEE";
}

void Board::IniciaTablero()
{
	std::string skill = "->+2";
	std::string sprite = "yippie";
	Card carta = Card(1, 2, sprite, skill);

	mazo.push_back(&carta);

}
