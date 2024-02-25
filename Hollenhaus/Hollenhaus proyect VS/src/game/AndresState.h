#pragma once
#include "checkML.h"
#include "GameState.h"


class Entity;
class GameState;

class AndresState :
    public GameState
{
public:
    AndresState();
    virtual ~AndresState();


    void refresh() override;
    void update() override;
    void render() const override;

private:
    ecs::entity_t card;

};

