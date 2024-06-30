#pragma once

#include <game/ecs.h>


class SolCardFactory {


public:

	SolCardFactory();
	~SolCardFactory();

	ecs::entity_t CreateCard(int, int, bool, Vector2D);

	//crea una carta con un indice 1-52

	ecs::entity_t CreateCardByIndex(int, bool, Vector2D);

	ecs::entity_t CreateCasillaDcha(int, Vector2D);

	void createCardsBoard(std::vector<int> indices);

	void number10Execption(int tipo, Vector2D pos, ecs::entity_t card);

	Vector2D startPosCardsOnBoard = Vector2D(100, 20);

	float boardCardsOffsetX = 100;
	float boardCardsOffsetY = 20;
private:

	//ini && fin, inclusive
	void setCardsReferences(std::vector<SolCardComponent*>& cards, int ini,int fin);

	Vector2D cardScale = Vector2D(0.8, 0.8);
	Vector2D iconBigScale = Vector2D(0.8, 0.8);
	Vector2D iconSmallScale = Vector2D(0.4, 0.4);
	Vector2D reverseScale = Vector2D(1, 1);

	int cardLayer = 1;
	int iconsLayer = 2; //debe ser mayor que cardLayer
	int reverseLayer = 3; //debe ser mayor que el resto
	Vector2D iconBigOffset = Vector2D(10, 31);
	Vector2D iconSmallOffset = Vector2D(30, 2);
	Vector2D numberOffset = Vector2D(15, 15);

	SDL_Color col; //color del numero de la carta
	std::string textoCarta; //numero o letra que va a ir en la carta

	//creacion de las cartas del tablero

};
