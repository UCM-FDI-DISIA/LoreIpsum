#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class SamuState :
    public GameState
{
public:
    SamuState();
    virtual ~SamuState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:
    ecs::entity_t card;
    ecs::entity_t board;

};

