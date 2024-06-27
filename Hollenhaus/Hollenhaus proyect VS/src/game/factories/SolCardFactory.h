#pragma once

#include <game/ecs.h>


class SolCardFactory {


public:

	SolCardFactory();
	~SolCardFactory();

	ecs::entity_t CreateCard(int, int, bool, Vector2D);

	ecs::entity_t CreateCasillaDcha(int, Vector2D);

private:

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
};
