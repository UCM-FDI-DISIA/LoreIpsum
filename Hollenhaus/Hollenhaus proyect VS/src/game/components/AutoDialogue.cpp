#include "pch.h"
#include "AutoDialogue.h"
#include "NextText.h"

AutoDialogue::AutoDialogue(int cd) 
	: cooldown(cd)
{
	count = 0;
	
}

void AutoDialogue::initComponent()
{
	nexttxt = getEntity()->getComponent<NextText>(); 
}

void AutoDialogue::update()
{
	// tiempo de espera
	if (count < cooldown) {

		count++;
	}
	else {

		// llama a next text
		// nexttext->NextText();

		count = 0;
	}
	

}
