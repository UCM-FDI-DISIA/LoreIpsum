#include "pch.h"
#include "DialogueReader.h"
#include "../../sdlutils/SDLUtils.h"
#include "TypeWriter.h"
#include "DialogueEventCollection.h"
#include "DialogueDestroyer.h"
#include "../Entity.h"

DialogueReader::DialogueReader(std::string owner, int convo, int firstNode)
{
	convo_ = &sdlutils().dialogues().at(owner).Convo(convo);
	actualNode_ = firstNode;
}

void DialogueReader::initComponent() {

	typeWriter_ = ent_->getComponent<TypeWriter>();
	assert(typeWriter_ != nullptr);

	//eventCollection_ = ent_->getComponent<DialogueEventCollection>();
	//assert(eventCollection_ != nullptr);

	dialogueDestroyer_ = ent_->getComponent<DialogueDestroyer>();
	assert(dialogueDestroyer_ != nullptr);

	typeWriter_->typeWrite(convo_->Node(actualNode_).Text());
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventStart());
}
void DialogueReader::NextNode()
{
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventFinish(), 0);
	actualNode_++;
	if (actualNode_ >= convo_->NodesVector().size()) {
		dialogueDestroyer_->destroyDialogue();
		return;
	}
	typeWriter_->typeWrite(convo_->Node(actualNode_).Text());
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventStart());
}

