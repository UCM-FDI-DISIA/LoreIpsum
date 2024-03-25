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
	if (finaltext != text) {

		if (speedCounter < writingSpeed) {

			speedCounter++;
		}
		else {

			finaltext.insert(finaltext.end(), text[i]);

			i++;

			setText();

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
}


