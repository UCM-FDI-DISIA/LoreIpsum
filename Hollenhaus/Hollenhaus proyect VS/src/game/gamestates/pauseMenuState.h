#pragma once
#include "GameState.h"
class pauseMenuState : public GameState
{
public:
    pauseMenuState();
    virtual ~pauseMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

