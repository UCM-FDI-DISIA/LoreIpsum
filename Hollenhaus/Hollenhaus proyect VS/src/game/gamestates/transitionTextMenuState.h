#pragma once
#include "../../sdlutils/RandomNumberGenerator.h"
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
    ecs::entity_t chascarrillo;
    std::string Ctext;

    ecs::entity_t casoText;
    ecs::entity_t casoNum;
    int caso;
    ecs::entity_t dineroText;
    ecs::entity_t dineroNum;
    int money;    
    
    ecs::entity_t almasText;
    ecs::entity_t almasNum;
    int almas;

    RandomNumberGenerator& rand_;

    ecs::entity_t continuar;
};

