#pragma once
#include "ComponentUpdate.h"
#include "TypeWriter.h"

class NextText;


class AutoDialogue : public ComponentUpdate
{
public:
	AutoDialogue(int cd);

	~AutoDialogue() override
	{
	}

	void initComponent() override;
	void update() override;

private:
	int cooldown;
	int count;

	NextText* nexttxt;
	TypeWriter* writer;
};
