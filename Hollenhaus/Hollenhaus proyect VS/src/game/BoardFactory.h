#pragma once
#include "Factory.h"


class Entity;
class BoardFactory : public Factory
{
public:
	BoardFactory(int w, int h);

	ecs::Entity* createBoard() override;

private:
	int width;
	int heigth;
};

