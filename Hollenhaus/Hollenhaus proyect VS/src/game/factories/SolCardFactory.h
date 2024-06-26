#pragma once

#include <game/ecs.h>


class SolCardFactory {


public:

	SolCardFactory();
	~SolCardFactory();

	ecs::entity_t CreateCard(int, int, bool);

private:

	Vector2D cardScale = Vector2D(1, 1);
	Vector2D iconBigScale = Vector2D(0.9, 0.9);
	Vector2D iconSmallScale = Vector2D(0.3, 0.3);

	int cardLayer = 1;
	int iconsLayer = 2; //debe ser mayor que cardLayer

	Vector2D iconBigOffset = Vector2D(-2, 29);
	Vector2D iconSmallOffset = Vector2D(50, 2);


};
