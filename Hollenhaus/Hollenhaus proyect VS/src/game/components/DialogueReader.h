#pragma once
#include "ComponentUpdate.h"
#include <string>

#include "..\Namespaces.h"

class TypeWriter;
class DialogueEventCollection;
class DialogueDestroyer;

class DialogueReader : public ComponentUpdate
{
public:
	DialogueReader(std::string owner, int convo, int firstNode = 0);
	void initComponent() override;
	void NextNode();

	void exeEvents(std::vector<JsonData::DialogueEventS> events);

private:
	JsonData::ConvoData* convo_;
	int actualNode_;

	TypeWriter* typeWriter_;
	DialogueEventCollection* eventCollection_;
	DialogueDestroyer* dialogueDestroyer_;
};

