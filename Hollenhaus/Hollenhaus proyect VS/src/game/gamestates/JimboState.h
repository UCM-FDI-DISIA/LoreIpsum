#pragma once
#include "GameState.h"

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
    ecs::entity_t legend_;
};

