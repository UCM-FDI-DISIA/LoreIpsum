#include "pch.h"
#include "DecisionFactory_V0.h"


void DecisionFactory_V0::createPopUp(Vector2D pos, Vector2D size)
{
	ecs::entity_t accept = Instantiate();



	ecs::entity_t deny = Instantiate();

}

void DecisionFactory_V0::setTextValues(std::string fid, SDL_Color c, Text::BoxPivotPoint bpp, Text::TextAlignment ta)
{
	fontID = fid;
	color = c;
	boxPivotPoint = bpp;
	textAlignment = ta;
}
