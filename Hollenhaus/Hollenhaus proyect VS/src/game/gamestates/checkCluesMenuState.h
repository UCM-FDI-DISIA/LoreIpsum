#pragma once

#include "GameState.h"

class checkCluesMenuState : public GameState
{
    checkCluesMenuState();
    virtual ~checkCluesMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};
