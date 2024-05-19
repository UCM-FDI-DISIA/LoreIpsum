#pragma once

//Checkml
#include <game/checkML.h>

#include "DialogueFactory.h"

class DialogueFactory_V0 : public DialogueFactory {

public:

	ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
		int speed, int cooldown, ecs::entity_t parent, int layer, bool auto_) override;

	void setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp, Text::TextAlignment ta) override;

private:

	std::string fontID;
	SDL_Color color;
	Uint32 wrapLenght;
	Text::BoxPivotPoint boxPivotPoint;
	Text::TextAlignment textAlignment;
};