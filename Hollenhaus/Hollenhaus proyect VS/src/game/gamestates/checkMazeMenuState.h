#pragma once

#include "GameState.h"

class checkMazeMenuState : public GameState
{
    checkMazeMenuState();
    virtual ~checkMazeMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};