#pragma once
#include "../pch.h"


class DecisionFactory
{
public:
	DecisionFactory() {};
	virtual ~DecisionFactory() {};

	virtual void createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer) = 0;

	virtual void setTextValues(std::string fid, SDL_Color c, Text::BoxPivotPoint bpp, Text::TextAlignment ta) = 0;
};

