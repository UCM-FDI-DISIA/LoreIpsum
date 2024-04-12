#pragma once
#include "GameState.h"
class storyModeState : public GameState
{
public:
    storyModeState();
    virtual ~storyModeState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};