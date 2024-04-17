#pragma once
#include "../pch.h"
#include "ComponentUpdate.h"

class DialogueBoxDestroyer : public ComponentUpdate
{
public:
	DialogueBoxDestroyer(ecs::entity_t child_);
	~DialogueBoxDestroyer() {}

	void initComponent() override;
	void update() override;

	void destroy();

private:
	ecs::entity_t text;
};

