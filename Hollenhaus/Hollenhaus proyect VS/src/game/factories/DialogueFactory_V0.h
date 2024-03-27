#pragma once
#include "DialogueFactory.h"

class DialogueFactory_V0 : public DialogueFactory {

public:
	DialogueFactory_V0() : DialogueFactory() {};
	virtual ~DialogueFactory_V0() {};

	ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
		int speed, int cooldown, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint,
		Text::TextAlignment textAlignment) override;
};