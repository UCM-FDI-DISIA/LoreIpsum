#include "pch.h"
#include "TypeWriterComponent.h"

TypeWriter::TypeWriter(int speed) :
speedCounter(0), writingSpeed(speed)
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

	while (true) {

		//
		if (speedCounter < writingSpeed) {

			// mete un caraacter mas al texto
			finaltxt.insert(finaltxt.end(), text[i]);

			i++;

			// crea un ttf con el texto

			speedCounter++;
		}
		else {
			speedCounter = 0;
		}

	}

}
