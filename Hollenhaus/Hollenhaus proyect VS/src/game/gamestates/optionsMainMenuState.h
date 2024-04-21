#pragma once

#include "GameState.h"

class OptionsMainMenuState : public GameState
{
public:
    OptionsMainMenuState();
    virtual ~OptionsMainMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:
    ecs::entity_t returnButton;
};

