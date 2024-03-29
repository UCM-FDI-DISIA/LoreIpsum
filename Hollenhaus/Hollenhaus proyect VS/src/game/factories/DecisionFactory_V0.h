#pragma once
#include "DecisionFactory.h"

class DecisionFactory_V0 : public DecisionFactory
{
public:
	DecisionFactory_V0() : DecisionFactory() {};
	virtual ~DecisionFactory_V0() {};

    void createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent) override;

	void setTextValues(std::string fid, SDL_Color c, Text::BoxPivotPoint bpp, Text::TextAlignment ta) override;

private:
	std::string fontID;
	SDL_Color color;
	Text::BoxPivotPoint boxPivotPoint;
	Text::TextAlignment textAlignment;
};

