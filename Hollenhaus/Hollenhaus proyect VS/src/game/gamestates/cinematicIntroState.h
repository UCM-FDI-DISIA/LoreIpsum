#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class CinematicIntroState : public GameState
{
public:
    CinematicIntroState();
    virtual ~CinematicIntroState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void onSkip();
};