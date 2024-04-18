#pragma once
#include "GameState.h"
class StoryModeState : public GameState
{
public:
    StoryModeState();
    virtual ~StoryModeState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};