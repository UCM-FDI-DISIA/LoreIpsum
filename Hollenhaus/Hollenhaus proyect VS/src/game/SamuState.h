#pragma once
#include "BoardFactory_v0.h"
#include "checkML.h"
#include "GameState.h"
#include "CardFactory_v0.h"

class Entity;
//class Manager;
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

