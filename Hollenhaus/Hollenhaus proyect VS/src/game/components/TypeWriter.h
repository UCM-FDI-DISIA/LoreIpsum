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
	void finishTypewrite();

	bool ended();

private:
	int speedCounter;
	int writingSpeed;
	int i;

	bool writing;

	std::string text, finaltext;

	void setText();

};