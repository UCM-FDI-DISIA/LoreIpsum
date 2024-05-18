#include <../pchs/pch.h>
#include "DialogueBoxDestroyer.h"
#include "../components/DialogueDestroyer.h"
#include "../components/FadeComponent.h"

DialogueBoxDestroyer::DialogueBoxDestroyer(ecs::entity_t child_)
{
	text = child_;
}

void DialogueBoxDestroyer::initComponent()
{
}

void DialogueBoxDestroyer::update()
{
	if (this->getEntity()->getComponent<SpriteRenderer>() != nullptr
		&& this->getEntity()->getComponent<FadeComponent>() != nullptr) {
		if (this->getEntity()->getComponent<SpriteRenderer>()->getOpacity() == 0
			&& !this->getEntity()->getComponent<FadeComponent>()->getFadeIn()) {

			continueDestroy();

		}
	}
}

void DialogueBoxDestroyer::destroy()
{
	//text->getComponent<FadeComponent>()->FadeIn();
}

void DialogueBoxDestroyer::continueDestroy()
{
	text->getComponent<DialogueDestroyer>()->destroyDialogue();
}
