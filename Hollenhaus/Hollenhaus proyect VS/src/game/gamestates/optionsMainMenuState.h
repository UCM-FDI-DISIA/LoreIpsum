#pragma once

#include "GameState.h"

class optionsMainMenuState : public GameState
{
    optionsMainMenuState();
    virtual ~optionsMainMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

