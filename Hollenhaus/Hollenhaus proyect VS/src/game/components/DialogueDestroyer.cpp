#include <../pchs/pch.h>

#include "DialogueDestroyer.h"
#include "../Game.h"
#include "../components/NPC.h"
#include "../components/NextText.h"
#include "../components/FadeComponent.h"


DialogueDestroyer::DialogueDestroyer(ecs::entity_t npc_)
{
	npc = npc_;
}

void DialogueDestroyer::initComponent()
{
	object = ent_;

}

void DialogueDestroyer::update()
{
	if (object->getComponent<FadeComponent>()->getFadeOut() 
		&& object->getComponent<FadeComponent>()->getProgress() == 0.0) {
		continueDestroy();
	}
}

void DialogueDestroyer::destroyDialogue()
{
	/*if (object->getComponent<FadeComponent>() == nullptr) TuVieja("no hay fade component");

	object->getComponent<FadeComponent>()->setFadeInFalse();
	auto e = object->getComponent<Transform>()->getParent()->getParent()->getChildren();
	auto it = e.begin();
	(*it)->getEntity()->getComponent<FadeComponent>()->setFadeInFalse();*/

	continueDestroy();
}

void DialogueDestroyer::continueDestroy()
{
	/*auto e = object->getComponent<Transform>()->getParent()->getParent()->getChildren();
	auto it = e.begin();
	(*it)->getEntity()->getComponent<FadeComponent>()->setFadeOutTrue();*/

	if (npc->hasComponent<NPC>()) {
		npc->getComponent<NPC>()->stoppedTalking();
	}
	object->getComponent<Transform>()->getParent()->getParent()->killChildren();
	object->getComponent<Transform>()->killChildren();

	object->setAlive(false);
}
