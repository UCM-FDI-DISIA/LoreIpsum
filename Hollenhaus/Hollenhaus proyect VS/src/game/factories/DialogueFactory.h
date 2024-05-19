#pragma once

//Checkml
#include <game/checkML.h>



class DialogueFactory
{
public:
	DialogueFactory() {};
	virtual ~DialogueFactory() {};

	virtual ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos,
		int speed, int cooldown, ecs::entity_t parent, int layer, bool auto_) = 0;

	virtual void setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp, 
		Text::TextAlignment ta) = 0;

};
