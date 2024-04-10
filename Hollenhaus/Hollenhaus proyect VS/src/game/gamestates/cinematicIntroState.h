#pragma once

#include "GameState.h"

class cinematicIntroState : public GameState
{
    cinematicIntroState();
    virtual ~cinematicIntroState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};