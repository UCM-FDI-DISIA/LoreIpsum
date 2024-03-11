#pragma once
#include "checkML.h"
#include "GameState.h"

class GameState;

class LuisState :
    public GameState
{
public:
    LuisState();
    virtual ~LuisState();


    void refresh() override;
    void update() override;
    void render() const override;

private:
    ecs::entity_t card;

};

