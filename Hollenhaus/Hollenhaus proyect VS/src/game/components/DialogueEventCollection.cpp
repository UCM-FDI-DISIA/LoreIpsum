#include "pch.h"
#include "DialogueEventCollection.h"

DialogueEventCollection::DialogueEventCollection()
{

}

void DialogueEventCollection::ChangeScene(int scene)
{
	std::cout << "Change to: " << scene << std::endl;
	GameStateMachine::instance()->setState(scene);
}
