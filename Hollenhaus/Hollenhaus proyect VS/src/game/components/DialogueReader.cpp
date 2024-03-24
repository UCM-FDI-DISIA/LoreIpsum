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

	//typeWriter_->setText(convo_->Node(actualNode_));
}
void DialogueReader::NextNode()
{
	actualNode_++;
	//typeWriter_->setText(convo_->Node(actualNode_));
}

