#pragma once
#include "DecisionFactory.h"

class DecisionFactory_V0 : public DecisionFactory
{
public:
	DecisionFactory_V0() : DecisionFactory() {};
	virtual ~DecisionFactory_V0() {};

    void createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer) override;

	void setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp, Text::TextAlignment ta) override;

private:
	std::string fontID;
	SDL_Color color;
	Uint32 wrapLenght;
	Text::BoxPivotPoint boxPivotPoint;
	Text::TextAlignment textAlignment;
};

