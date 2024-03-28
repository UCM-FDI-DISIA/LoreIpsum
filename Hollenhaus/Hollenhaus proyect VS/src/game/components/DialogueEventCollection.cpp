#include "pch.h"
#include "DialogueEventCollection.h"

DialogueEventCollection::DialogueEventCollection()
{

}

void DialogueEventCollection::ChangeScene(int scene)
{
	GameStateMachine::instance()->setState(scene);
}
