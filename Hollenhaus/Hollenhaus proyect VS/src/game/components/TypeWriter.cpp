#include "pch.h"
#include "TypeWriter.h"
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
	finaltext = " ";
	text = " ";
	i = 0;
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


void TypeWriter::typeWrite(std::string newtext)
{

	finaltext.clear();
	//finaltext = "";
	text = newtext;
	std::cout << newtext << std::endl;

	i = 0;
}

void TypeWriter::finishTypewrite()
{
	finaltext = text;
	// actualiza el texto
	setText();
}

bool TypeWriter::ended()
{
	return finaltext == text;
}

void TypeWriter::setText()
{
	getEntity()->getComponent<TextComponent>()->setTxt(finaltext);
}
