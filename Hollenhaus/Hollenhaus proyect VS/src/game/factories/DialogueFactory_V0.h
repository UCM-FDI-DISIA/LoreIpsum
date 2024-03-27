#pragma once
#include "DialogueFactory.h"

class DialogueFactory_V0 : public DialogueFactory {

	DialogueFactory_V0() : DialogueFactory() {};
	~DialogueFactory_V0() {};

	ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
		int speed, int cooldown, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint,
		Text::TextAlignment textAlignment) override;
};