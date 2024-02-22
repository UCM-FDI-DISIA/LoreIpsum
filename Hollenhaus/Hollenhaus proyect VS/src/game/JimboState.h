#pragma once
#include "GameState.h"
#include "checkML.h"

class Entity;
class Transform;

class JimboState :
    public GameState
{
public:
    JimboState();
    virtual ~JimboState();


    void refresh() override;
    void update() override;
    void render() const override;

private:
    ecs::entity_t card_;
    ecs::entity_t card2_;
    Transform* transform;
    Transform* transform2;
};

