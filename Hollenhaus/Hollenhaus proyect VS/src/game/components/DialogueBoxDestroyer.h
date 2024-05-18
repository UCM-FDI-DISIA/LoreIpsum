#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

class DialogueBoxDestroyer : public ComponentUpdate
{
public:
	DialogueBoxDestroyer(ecs::entity_t child_);
	~DialogueBoxDestroyer() {}

	void initComponent() override;
	void update() override;

	void destroy();
	void continueDestroy();

private:
	ecs::entity_t text;
};

