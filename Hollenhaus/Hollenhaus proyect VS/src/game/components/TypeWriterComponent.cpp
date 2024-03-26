#include "pch.h"
#include "TypeWriterComponent.h"
#include "basics/TextComponent.h"
#include "../Game.h"

TypeWriter::TypeWriter(int speed) :
speedCounter(0), writingSpeed(speed)
{
	finaltext = " ";
	text = " ";
	i = 0;
}

TypeWriter::~TypeWriter()
{
}

void TypeWriter::initComponent()
{
}

void TypeWriter::update()
{
	// si no ha acabado de escribir
	if (finaltext != text) {

		// tiempo de espera
		if (speedCounter < writingSpeed) {

			speedCounter++;
		}
		else {

			// suma el char siguiente a finaltext
			finaltext.insert(finaltext.end(), text[i]);

			// cuenta para el siguiente char
			i++;

			// actualiza el texto
			setText();

			// reinicia el contador
			speedCounter = 0;
		}
	}
}

// setea la informacion para escribir
void TypeWriter::typeWrite(std::string newtext)
{
	finaltext = "";
	text = newtext;
	i = 0;
}

void TypeWriter::setText()
{
	getEntity()->getComponent<TextComponent>()->setTxt(finaltext);
	//sugerencia: 
	//ent_->getComponent<TextComponent>()->setTxt(finaltext);
}