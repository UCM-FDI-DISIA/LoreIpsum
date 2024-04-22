#include <../pchs/pch.h>
#include "DialogueBoxDestroyer.h"
#include "../components/DialogueDestroyer.h"

DialogueBoxDestroyer::DialogueBoxDestroyer(ecs::entity_t child_)
{
	text = child_;
}

void DialogueBoxDestroyer::initComponent()
{
}

void DialogueBoxDestroyer::update()
{
}

void DialogueBoxDestroyer::destroy()
{
	text->getComponent<DialogueDestroyer>()->destroyDialogue();
}
