#pragma once
#include "ComponentUpdate.h"

class TextComponent;

class PasteOnTextComponentButton : public ComponentUpdate
{
public:
	PasteOnTextComponentButton(TextComponent* textComponent);
	~PasteOnTextComponentButton() override;

	void initComponent() override;
	void update() override;

private:
	void clickButton();

	TextComponent* tc;
	BoxCollider* bc;
};
