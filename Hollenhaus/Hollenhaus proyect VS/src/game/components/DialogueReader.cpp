#include <../pchs/pch.h>

#include "DialogueReader.h"
#include "../../sdlutils/SDLUtils.h"
#include "TypeWriter.h"
#include "DialogueEventCollection.h"
#include "DialogueDestroyer.h"
#include "../Entity.h"
#include "../components/NextText.h"

DialogueReader::DialogueReader(std::string owner, int convo, int firstNode)
{

	own = owner;
	conv = convo;
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

	//convo_->Node(2);
	if (convo_ == nullptr) return;
	typeWriter_->typeWrite(convo_->Node(actualNode_).Text());
	exeEvents(convo_->Node(actualNode_).NodeEventsStart());

}
void DialogueReader::NextNode()
{
	if (ent_ == nullptr) return;
	if (ent_->getComponent<NextText>() == nullptr) return;
	if (!ent_->getComponent<NextText>()->isDead()) {

		//std::cout << convo_->Node(actualNode_).NodeID() << std::endl;
		//std::cout << convo_->ConvoID() << std::endl << std::endl;

		convo_->Node(actualNode_).NodeEventsFinish();

		exeEvents(convo_->Node(actualNode_).NodeEventsFinish());
		actualNode_++;
		if (actualNode_ >= convo_->NodesVector().size()) {
			ent_->getComponent<NextText>()->setDead(true);
			dialogueDestroyer_->destroyDialogue();
			return;
		}
		typeWriter_->typeWrite(convo_->Node(actualNode_).Text());
		exeEvents(convo_->Node(actualNode_).NodeEventsStart());
	}
}

void DialogueReader::destroyDialogue()
{
	if (ent_->hasComponent<NextText>()) {
		ent_->getComponent<NextText>()->setDead(true);
		dialogueDestroyer_->destroyDialogue();
	}
}

void DialogueReader::exeEvents(std::vector<JsonData::DialogueEventS> events)
{
	for (auto e : events) {
		eventCollection_->callEvent(e.getType(), e.getScene(), getEntity(), e.getGreenDecision(), e.getredDecision())();
	}
}