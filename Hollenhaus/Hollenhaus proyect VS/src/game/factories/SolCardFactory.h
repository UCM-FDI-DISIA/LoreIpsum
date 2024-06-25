#pragma once

#include <game/ecs.h>


class SolCardFactory {


public:

	SolCardFactory();
	~SolCardFactory();

	ecs::entity_t CreateCard();

private:

	Vector2D cardScale = Vector2D(1,1);
	Vector2D iconScale = Vector2D(1,1);

	int cardLayer = 1;
	int iconLayer = 2;//debe ser mayor que cardLayer

	Vector2D iconBigOffset = Vector2D(3, 35);


};
