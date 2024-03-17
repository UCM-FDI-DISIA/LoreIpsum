#pragma once
#include "ComponentUpdate.h"
#include <string>


class TypeWriter : public ComponentUpdate
{
public:
	TypeWriter(int writingSpeed);
	~TypeWriter();

	void initComponent() override;
	void update() override;

	void typeWrite(std::string text);

private:
	int speedCounter;
	int writingSpeed;

};