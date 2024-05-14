#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

class TextComponent;

class PasteOnTextComponentButton : public ComponentUpdate
{
public:
    PasteOnTextComponentButton(TextComponent* textComponent);
    ~PasteOnTextComponentButton();

    void initComponent() override;
    void update() override;

private:
    void clickButton();

    TextComponent* tc;
    BoxCollider* bc;
};

