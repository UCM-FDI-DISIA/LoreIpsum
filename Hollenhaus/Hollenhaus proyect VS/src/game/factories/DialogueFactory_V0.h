#pragma once
#include "DialogueFactory.h"

class DialogueFactory_V0 : public DialogueFactory {

	DialogueFactory_V0() {};
	~DialogueFactory_V0() {};

	ecs::entity_t createDialogue(std::string id, int convo, int node) override;
};