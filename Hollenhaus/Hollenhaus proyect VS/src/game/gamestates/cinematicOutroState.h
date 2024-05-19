#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class CinematicOutroState : public GameState
{
public:
    CinematicOutroState();
    virtual ~CinematicOutroState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};