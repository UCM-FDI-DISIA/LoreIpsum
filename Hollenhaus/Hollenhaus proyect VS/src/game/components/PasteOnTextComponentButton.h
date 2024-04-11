#pragma once
#include "ComponentUpdate.h"

class TextComponent;

class PasteOnTextComponentButton : public ComponentUpdate
{
public:
    PasteOnTextComponentButton();
    ~PasteOnTextComponentButton();

    void initComponent() override;
    void update() override;

private:
    void clickButton();

    TextComponent* tc;
    BoxCollider* bc;
};

