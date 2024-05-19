#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"
class StoryModeState : public GameState
{
public:
    StoryModeState();
    virtual ~StoryModeState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void newGameStart();

private:

    ecs::entity_t newGameButton;
    ecs::entity_t continueButton;
    ecs::entity_t returnButton;

};