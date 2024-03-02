#pragma once
#include "Factory.h"


class Entity;
class BoardFactory 
{
public:
	BoardFactory(int w, int h);

	ecs::Entity* createBoard() ;

private:
	int width;
	int heigth;
};

