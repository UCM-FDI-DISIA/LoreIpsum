#pragma once

//Checkml
#include <game/checkML.h>

//forward declaration
namespace ecs {
	class Entity;
	using entity_t = Entity*;
}


class BoardFactory
{
public:
	BoardFactory(int size) : size (size){};

	virtual ~BoardFactory(){};

	virtual ecs::entity_t createBoard() = 0;

protected:
	int size;

};

