#include "Board.h"
#include <iostream>
#include <stdLib.h>

Board::Board()
{
	IniciaTablero();

	// prepara el color para consola con Windows.h
	//HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);



}

void Board::PaintBoard()
{
	// para colorear poner 
	// system("Color E4");
	// siendo E el color de fondo y 4 el del texto
	// despues poner de vuelta el 
	// system("Color 07") para blanco y negro

	for (int i = 0; i < mazo.size(); i++) {

		// pinta la carta
		std::cout << GetCard(nullptr);

		// cada 4 hace un salto de linea
		if (i % 4 == 0) {
			std::cout << "\n";
		}

	}

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

	/*
	std::string skill = "->+2";
	std::string sprite = "yippie";
	Card carta = Card(1, 2, sprite, skill);

	mazo.push_back(&carta);*/

}
