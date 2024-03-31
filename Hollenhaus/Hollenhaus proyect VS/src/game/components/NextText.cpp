#include "pch.h"
#include "NextText.h"
#include "managers/Manager.h"
#include "DialogueDestroyer.h"

//Detecta el clickIzq con el BoxCollider del cuadro de texto (o de la pantalla?) y hace las siguientes operaciones:
//->Se llama al EventoFinal del texto actual
//->JSONReader pasa al siguiente texto
//->TypeWriter se reinicia

NextText::NextText()
{
	click = false;
	boxCollider_ = nullptr;
	dead = false;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

NextText::~NextText()
{

}

void NextText::initComponent()
{
	boxCollider_ = ent_->getComponent<BoxCollider>(); //collider del dialogo
	assert(boxCollider_ != nullptr);

	dialogueReader_ = ent_->getComponent<DialogueReader>();
	assert(dialogueReader_ != nullptr);

	typeWriter_ = ent_->getComponent<TypeWriter>();
	assert(typeWriter_ != nullptr);
}

void NextText::update()
{
}

void NextText::OnLeftClickDown()
{
	click = true;
	reactToClick();
}

void NextText::OnLeftClickUp()
{
	click = false;
}

void NextText::reactToClick()
{
	if (!dead) {
		if (typeWriter_->ended() && mouseRaycast() == ent_)
		{
			TuVieja("ended: ");
			//TuVieja(typeWriter_->ended());
			dialogueReader_->NextNode();
		}
	}
	
}

void NextText::callNextNode()
{
	if (typeWriter_->ended()) {
		TuVieja("Cambio de nodo.");
		dialogueReader_->NextNode();
	}
}

void NextText::setDead(bool a)
{
	this;
	dead = a;
}


