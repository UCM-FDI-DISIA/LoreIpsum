#pragma once
#include "ComponentUpdate.h"
#include "TypeWriter.h"

class NextText;
//class TypeWriterComponent;


class AutoDialogue : public ComponentUpdate
{
public:
	AutoDialogue(int cd);
	~AutoDialogue() {}

	void initComponent() override;
	void update() override;

private:
	
	int cooldown;
	int count;

	NextText* nexttxt;
	TypeWriter* writer;

};