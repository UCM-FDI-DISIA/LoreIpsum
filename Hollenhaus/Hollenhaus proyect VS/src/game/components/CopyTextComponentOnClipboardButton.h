#pragma once
#include "ComponentUpdate.h"

class TextComponent;

class CopyTextComponentOnClipboardButton : public ComponentUpdate
{
public:
	CopyTextComponentOnClipboardButton();
	~CopyTextComponentOnClipboardButton();

	void initComponent() override;
	void update() override;

private:
	void clickButton();

	TextComponent* tc;
	BoxCollider* bc;
};

