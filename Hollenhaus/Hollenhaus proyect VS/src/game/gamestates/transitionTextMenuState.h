#pragma once
#include "GameState.h"
class TransitionTextMenuState : public GameState
{
public:
    TransitionTextMenuState();
    virtual ~TransitionTextMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:
    ecs::entity_t dineroText;
    ecs::entity_t dineroNum;
    int money;

    ecs::entity_t continuar;
};

