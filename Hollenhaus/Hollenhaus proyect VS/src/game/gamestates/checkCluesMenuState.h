#pragma once

#include "GameState.h"

class CheckCluesMenuState : public GameState
{
public:
    CheckCluesMenuState();
    virtual ~CheckCluesMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};
