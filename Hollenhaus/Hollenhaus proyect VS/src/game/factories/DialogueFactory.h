#pragma once
#include "../pch.h"


class DialogueFactory
{
public:
	DialogueFactory() {};
	virtual ~DialogueFactory() {};

	virtual ecs::entity_t createDialogue(std::string id, int convo, int node) = 0;

};
