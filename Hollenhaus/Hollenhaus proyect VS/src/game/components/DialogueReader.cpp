#include "pch.h"
#include "DialogueReader.h"
#include "../../sdlutils/SDLUtils.h"
#include "TypeWriterComponent.h"
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

	//typeWriter_->setText(convo_->Node(actualNode_));
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventStart());
}
void DialogueReader::NextNode()
{
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventFinish());
	actualNode_++;
	if (actualNode_ >= convo_->NodesVector().size()) {
		//dialogueDestroyer_->DestroyDialogue();
		return;
	}
	//typeWriter_->setText(convo_->Node(actualNode_));
	//eventCollection_->callEvent(convo_->Node(actualNode_).NodeEventStart());
}

