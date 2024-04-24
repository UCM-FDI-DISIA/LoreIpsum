#include "ComponentUpdate.h"
#include "../../sdlutils/SDLUtils.h"
#include "../Namespaces.h"

#include "DialogueReader.h"
#include "TypeWriter.h"

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
	~NextText();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
	void OnLeftClickUp();
	void reactToClick();
	void callNextNode();
	void callFullText();
	void setDead(bool a);
	void setCollider(BoxCollider* coll);
	bool isDead() { return dead; }

private:
	bool click;
	bool dead;
	bool hasBC;

	TypeWriter* typeWriter_; //para reiniciarlo cuando se cambie de nodo
	DialogueReader* dialogueReader_;
	DialogueEventCollection* eventCollection_;
	BoxCollider* boxCollider_;
};

