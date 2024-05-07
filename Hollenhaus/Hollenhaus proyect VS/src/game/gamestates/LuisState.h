#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class Factory;

class LuisState :
    public GameState
{
public:
    LuisState();
    virtual ~LuisState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:
    Factory* factory;
};

