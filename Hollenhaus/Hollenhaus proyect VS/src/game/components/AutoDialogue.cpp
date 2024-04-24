#include <../pchs/pch.h>

#include "AutoDialogue.h"
#include "NextText.h"
#include "../components/TypeWriter.h"

AutoDialogue::AutoDialogue(int cd)
	: cooldown(cd)
{
	count = 0;
}

void AutoDialogue::initComponent()
{
	nexttxt = getEntity()->getComponent<NextText>();
	assert(nexttxt != nullptr);


	writer = getEntity()->getComponent<TypeWriter>();
	assert(writer != nullptr);
}

void AutoDialogue::update()
{
	// si ha acabado
	if (writer->ended())
	{
		// tiempo de espera
		if (count < cooldown)
		{
			count++;
		}
		else
		{
			// llama a next text
			nexttxt->callNextNode();

			//TuVieja("pasa");

			count = 0;
		}
	}
}
