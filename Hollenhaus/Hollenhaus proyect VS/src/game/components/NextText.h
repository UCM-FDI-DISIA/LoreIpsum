#include "ComponentUpdate.h"
#include "../../sdlutils/SDLUtils.h"
#include "..\Namespaces.h"

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
	~NextText() {}

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
	void OnLeftClickUp();
	void reactToClick();

private:
	bool click;

	TypeWriter* typeWriter_; //para reiniciarlo cuando se cambie de nodo
	DialogueReader* dialogueReader_;
	DialogueEventCollection* eventCollection_;
	BoxCollider* boxCollider_;

	//como hago para saber el numero total de nodes del json? vectornodes ??¿
	//if actualNode != nodeFinal cuando se hace clic -> hacemos actualNode++ (del dialoguereader)
	//else -> se acaba la convo (desaparece cuadro?), se reinicia actualNode a 0, y se llama al evento final si es que hay

};

