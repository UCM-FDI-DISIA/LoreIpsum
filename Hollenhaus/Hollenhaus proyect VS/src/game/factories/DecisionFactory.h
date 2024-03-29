#pragma once
#include "../pch.h"


class DecisionFactory
{
public:
	DecisionFactory() {};
	virtual ~DecisionFactory() {};

	virtual ecs::entity_t createPopUp(Vector2D pos, Vector2D size) = 0;

	virtual void setTextValues(std::string fid, SDL_Color c, Text::BoxPivotPoint bpp, Text::TextAlignment ta) = 0;
};

