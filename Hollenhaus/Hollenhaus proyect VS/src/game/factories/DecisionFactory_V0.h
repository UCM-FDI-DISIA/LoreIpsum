#pragma once

//Checkml
#include <game/checkML.h>

#include "DecisionFactory.h"
#include "../components/NextText.h"

/// <summary>
/// COMO CREAR LAS OPCIONES DESPUES DE UN DIALOGO. 24/04/24
/// 
/// 
/// </summary>

class DecisionFactory_V0 : public DecisionFactory
{
public:
	DecisionFactory_V0() : DecisionFactory() {};
	virtual ~DecisionFactory_V0() {};

    void createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer, int scene, int greenDecision, int redDecision) override;

	void setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp, Text::TextAlignment ta) override;

private:
	std::string fontID;
	SDL_Color color;
	Uint32 wrapLenght;
	Text::BoxPivotPoint boxPivotPoint;
	Text::TextAlignment textAlignment;
};

