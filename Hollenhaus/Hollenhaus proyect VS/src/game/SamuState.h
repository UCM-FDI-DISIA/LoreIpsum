#pragma once
#include "BoardFactory_v0.h"
#include "checkML.h"
#include "GameState.h"
#include "CardFactory_v0.h"

class Entity;
class GameState;

class SamuState :
    public GameState
{
public:
    SamuState();
    virtual ~SamuState();


    void refresh() override;
    void update() override;
    void render() const override;

private:
    ecs::entity_t card;
    ecs::entity_t board;
};

