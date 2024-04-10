#pragma once

#include "GameState.h"

class Factory;

class tutorialState : public GameState
{
	tutorialState();
    virtual ~tutorialState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

