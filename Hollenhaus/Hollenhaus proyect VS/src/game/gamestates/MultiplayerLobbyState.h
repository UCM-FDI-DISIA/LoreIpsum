#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class MultiplayerLobbyState
    :public GameState
{
public:
    MultiplayerLobbyState();
    virtual ~MultiplayerLobbyState();


    void refresh() override;
    void update() override;
    void render() const override;


    void onEnter() override;
    void onExit() override;

private:
};

