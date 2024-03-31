#include "pch.h"
#include "DialogueDestroyer.h"
#include "../Game.h"
#include "../components/NPC.h"


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

}

void DialogueDestroyer::destroyDialogue()
{

	npc->getComponent<NPC>()->stoppedTalking();
	object->~Entity();
}
