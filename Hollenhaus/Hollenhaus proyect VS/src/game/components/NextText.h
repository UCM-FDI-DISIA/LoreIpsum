#include "ComponentUpdate.h"
#include "TypeWriterComponent.h"
#include "../../sdlutils/SDLUtils.h"
#include "../Entity.h"
#include "..\Namespaces.h"

#pragma once
class NextText : public ComponentUpdate
{
public:
	NextText();
	~NextText() {}

	void initComponent() override;
	void update() override;

private:
	int nodeCounter;

	TypeWriter* typeWriter_; //para reiniciarlo cuando se cambie de nodo
	JsonData::ConvoData* convo_; //de aqui se obtiene convoId y vector nodes?¿
	int actualNode_; //nodo que se esta mostrando

	//como hago para saber el numero total de nodes del json? vectornodes ??¿
	//if actualNode != nodeFinal cuando se hace clic -> hacemos actualNode++
	//else -> se acaba la convo (desaparece cuadro?), se reinicia actualNode a 0, y se llama al evento final si es que hay

};

