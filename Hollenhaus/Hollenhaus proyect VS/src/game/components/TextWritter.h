#pragma once
#include "ComponentUpdate.h"

class TextComponent;

class TextWritter : public ComponentUpdate
{
public:
	TextWritter();
	~TextWritter();

	void initComponent() override;
	void update() override;

	void UpdateText(std::string s);
	void DeleteLastChar();
private:
	TextComponent* tc;
};

