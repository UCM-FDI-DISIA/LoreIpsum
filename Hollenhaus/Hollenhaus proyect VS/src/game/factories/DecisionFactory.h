#pragma once
#include <../pchs/pch.h>


class DecisionFactory
{
public:
	DecisionFactory()
	{
	};

	virtual ~DecisionFactory()
	{
	};

	virtual void createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer, int scene, int greenDecision,
	                         int redDecision) = 0;

	virtual void setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp,
	                           Text::TextAlignment ta) = 0;
};
