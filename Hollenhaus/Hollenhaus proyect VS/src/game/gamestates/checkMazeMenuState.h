#pragma once

#include "GameState.h"

class CheckMazeMenuState : public GameState
{
public:
    CheckMazeMenuState();
    virtual ~CheckMazeMenuState();

    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void ShowMaze();
    void CleanMazeMenu();

private:
    // Array auxiliar para guardar las cartas actuales del menu
    std::array<ecs::entity_t, 20> cardsAux;
};