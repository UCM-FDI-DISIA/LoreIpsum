#include "pch.h"
#include "NextText.h"

//Detecta el clickIzq con el BoxCollider del cuadro de texto (o de la pantalla?) y hace las siguientes operaciones:
//->Se llama al EventoFinal del texto actual
//->JSONReader pasa al siguiente texto
//->TypeWriter se reinicia

NextText::NextText()
{
	click = false;
	boxCollider_ = nullptr;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
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
	if (!click && boxCollider_->isCursorOver() && typeWriter_->ended()) {
		TuVieja("Cambio de nodo.");
		dialogueReader_->NextNode();
	}
}


