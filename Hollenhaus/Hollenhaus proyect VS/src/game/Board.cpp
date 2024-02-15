#include "Board.h"
#include <iostream>
#include <stdLib.h>

Board::Board()
{
	width = 4;
	height = 4;

	IniciaTablero();

	// prepara el color para consola con Windows.h
	//HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

}

void Board::PaintBoard()
{

	Card* card = nullptr;
	// para colorear poner 
	// system("Color E4");
	// siendo E el color de fondo y 4 el del texto
	// despues poner de vuelta el 
	// system("Color 07") para blanco y negro

	// hasta 16 porque es un 4x4 en principio
	for (int i = 0; i < (height*width); i++) {

		// recoge la carta
		card = mazo[i];


		// si no hay carta
		if (card == nullptr) {

			std::cout << "[ -/-/---- ]";
		}
		// si hay carta
		else {
			// gestiona el color
			if (card->getPlayer()) { system("Color E0"); }	// player color amarillo
			else { system("Color B0"); }					// npc color azulito

			// pinta la carta
			std::cout << GetCard(card);


			system("Color 07");	// vuelve al negro
		}

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
	return "YIIPIEE";
}

void Board::IniciaTablero()
{

	/*
	std::string skill = "->+2";
	std::string sprite = "yippie";
	Card carta = Card(1, 2, sprite, skill);

	mazo.push_back(&carta);*/

}
