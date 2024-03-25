#include "pch.h"
#include "NextText.h"

//Detecta el clickIzq con el BoxCollider del cuadro de texto (o de la pantalla?) y hace las siguientes operaciones:
//->Se llama al EventoFinal del texto actual
//->JSONReader pasa al siguiente texto
//->TypeWriter se reinicia

NextText::NextText() {

}

void NextText::initComponent()
{
	typeWriter_ = ent_->getComponent<TypeWriter>();
	//assert(typeWriter_ != nullptr);

}

void NextText::update()
{
}
