#include "pch.h"
#include "TypeWriterComponent.h"
#include "basics/TextComponent.h"

TypeWriter::TypeWriter(int speed) :
speedCounter(0), writingSpeed(speed * 1000)
{

}

TypeWriter::~TypeWriter()
{
}

void TypeWriter::initComponent()
{
}

void TypeWriter::update()
{
}

// escribe en typewrite el texto indicado
void TypeWriter::typeWrite(std::string text)
{

	
	std::string finaltxt;
	int i = 0;

	while (finaltxt != text) {

		//
		if (speedCounter < writingSpeed) {

			// mete un caraacter mas al texto
			finaltxt.insert(finaltxt.end(), text[i]);

			std::cout << finaltxt << std::endl;

			i++;

			getEntity()->getComponent<TextComponent>()->setTxt(finaltxt);

			// crea un ttf con el texto

			speedCounter++;
		}
		else {
			speedCounter = 0;
		}

	}

}
