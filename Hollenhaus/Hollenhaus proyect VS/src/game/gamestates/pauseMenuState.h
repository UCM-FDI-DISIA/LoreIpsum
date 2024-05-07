#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"
class PauseMenuState : public GameState
{
public:
    PauseMenuState();
    virtual ~PauseMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void setPreviousState(int ps)
    {
        previousState = ps;
    }

    int previousState;
    void onDespause();
};

