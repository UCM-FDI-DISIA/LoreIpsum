#pragma once
#include <../pchs/pch.h>

#include "ComponentUpdate.h"


class DialogueDestroyer : public ComponentUpdate
{
public:
	DialogueDestroyer(ecs::entity_t parent_);

	~DialogueDestroyer() override
	{
	}

	void initComponent() override;
	void update() override;

	void destroyDialogue();

private:
	ecs::entity_t npc;
	ecs::entity_t object;
};
