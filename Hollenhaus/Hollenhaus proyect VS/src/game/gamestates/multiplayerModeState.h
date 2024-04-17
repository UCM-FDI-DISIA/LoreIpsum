#pragma once

#include "GameState.h"

class MultiplayerModeState : public GameState
{
public:
    MultiplayerModeState();
    virtual ~MultiplayerModeState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:

    ecs::entity_t mainMenuButton;
    ecs::entity_t iniGameButton;

};

