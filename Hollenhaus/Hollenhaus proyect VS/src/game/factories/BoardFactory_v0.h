#pragma once

//Checkml
#include <game/checkML.h>

#include "BoardFactory.h"


class BoardFactory_v0 : public BoardFactory
{
public:
	BoardFactory_v0(int size) : BoardFactory(size) {};

	ecs::entity_t createBoard() override;

};

