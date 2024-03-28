#include "pch.h"
#include "DialogueDestroyer.h"
#include "../Game.h"


DialogueDestroyer::DialogueDestroyer()
{
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
	object->~Entity();
}
