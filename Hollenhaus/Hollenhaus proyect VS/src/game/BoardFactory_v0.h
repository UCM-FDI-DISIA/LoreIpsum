#pragma once


//forward declaration
namespace ecs {
	class Entity;
	using entity_t = Entity*;
}

class BoardFactory_v0 
{
public:
	BoardFactory_v0(int w, int h);

	ecs::entity_t createBoard() ;

private:
	int width;
	int heigth;
};

