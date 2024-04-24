#pragma once
#include "ComponentUpdate.h"

class TextWritter;

class InputForTextWritter : public ComponentUpdate
{
public:
	InputForTextWritter();
	~InputForTextWritter();

	void initComponent() override;
	void update() override;

private:
	TextWritter* tw;
};

