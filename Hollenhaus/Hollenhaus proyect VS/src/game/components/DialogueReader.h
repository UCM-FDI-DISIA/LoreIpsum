#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include <string>

#include "../Namespaces.h"

class TypeWriter;
class DialogueEventCollection;
class DialogueDestroyer;

class DialogueReader : public ComponentUpdate
{
public:
	DialogueReader(std::string owner, int convo, int firstNode = 0);
	void initComponent() override;
	void NextNode();

	void destroyDialogue();

private:
	JsonData::ConvoData* convo_;
	int actualNode_;
	int conv;
	std::string own;

	TypeWriter* typeWriter_ = nullptr;
	DialogueEventCollection* eventCollection_ = nullptr;
	DialogueDestroyer* dialogueDestroyer_ = nullptr;

	void exeEvents(std::vector<JsonData::DialogueEventS> events);

};

