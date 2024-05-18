#pragma once

//Checkml
#include <game/checkML.h>

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

    std::list<int> mazeAux;
    int cardsYPos[3] = {100, 250, 400};
};