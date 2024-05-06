#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"
class KeyMenuState :
    public GameState
{
public:
    KeyMenuState();
    ~KeyMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;
};

