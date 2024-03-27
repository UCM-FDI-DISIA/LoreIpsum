#pragma once
#include "../pch.h"


class DialogueFactory
{
public:
	DialogueFactory() {};
	virtual ~DialogueFactory() {};

	virtual ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
		int speed, int cooldown, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint,
		Text::TextAlignment textAlignment) = 0;

};
