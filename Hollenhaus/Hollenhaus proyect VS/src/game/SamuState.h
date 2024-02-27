#pragma once
#include "checkML.h"
#include "GameState.h"


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

    void onEnter() const override;
    void onExit() const override;

private:
    ecs::entity_t card;

};

