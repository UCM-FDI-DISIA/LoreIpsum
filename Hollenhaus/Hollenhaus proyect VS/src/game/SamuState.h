#pragma once
#include "checkML.h"
#include "GameState.h"


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
    ecs::entity_t manager;

};

