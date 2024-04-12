#pragma once
#include "GameState.h"
class transitionTextMenuState : public GameState
{
public:
    transitionTextMenuState();
    virtual ~transitionTextMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

