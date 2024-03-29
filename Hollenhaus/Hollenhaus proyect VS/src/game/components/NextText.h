#include "ComponentUpdate.h"
#include "../../sdlutils/SDLUtils.h"
#include "..\Namespaces.h"

#include "DialogueReader.h"
#include "TypeWriter.h"
#include "MoveOnClick.h"

//class TypeWriter;
class DialogueEventCollection;
class DialogueDestroyer;
//class DialogueReader;
class BoxCollider;

#pragma once
class NextText : public ComponentUpdate
{
public:
	NextText();
	~NextText() {}

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
	void OnLeftClickUp();
	void reactToClick();
	void callNextNode();

private:
	bool click;

	TypeWriter* typeWriter_; //para reiniciarlo cuando se cambie de nodo
	DialogueReader* dialogueReader_;
	DialogueEventCollection* eventCollection_;
	BoxCollider* boxCollider_;
	MoveOnClick* moveOnClick_;
};

