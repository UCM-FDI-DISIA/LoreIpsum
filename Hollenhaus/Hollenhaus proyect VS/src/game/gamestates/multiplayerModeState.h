#pragma once

#include "GameState.h"

class multiplayerModeState : public GameState
{
    multiplayerModeState();
    virtual ~multiplayerModeState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

