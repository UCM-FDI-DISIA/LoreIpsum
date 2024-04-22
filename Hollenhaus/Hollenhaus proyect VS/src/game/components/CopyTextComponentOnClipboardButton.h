#pragma once
#include "ComponentUpdate.h"

class TextComponent;
class BoxCollider;

// Este componente necesita un BoxCollider en su entidad para actuar de botón
// Además, debe recibir un textComponent (normalmente de otra entidad) para modificarlo al activar el botón
class CopyTextComponentOnClipboardButton : public ComponentUpdate
{
public:
	CopyTextComponentOnClipboardButton(TextComponent* textComponent);
	~CopyTextComponentOnClipboardButton();

	void initComponent() override;
	void update() override;

private:
	void clickButton();

	TextComponent* tc;
	BoxCollider* bc;
};

