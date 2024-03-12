#pragma once
#include "../checkML.h"
#include "GameState.h"

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
    ecs::entity_t hand_;

};

