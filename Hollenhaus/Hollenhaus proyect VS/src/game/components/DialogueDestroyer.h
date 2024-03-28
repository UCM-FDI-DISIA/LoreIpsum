#pragma once
#include "../pch.h"
#include "ComponentUpdate.h"


class DialogueDestroyer : public ComponentUpdate
{
public:
	DialogueDestroyer();
	~DialogueDestroyer() {}

	void initComponent() override;
	void update() override;

	void destroyDialogue();

private:
	
	ecs::entity_t object;
};
