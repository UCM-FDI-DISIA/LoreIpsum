#pragma once
#include "GameState.h"

class MultiplayerLobby
    :public GameState
{
public:
    MultiplayerLobby();
    virtual ~MultiplayerLobby();


    void refresh() override;
    void update() override;
    void render() const override;


    void onEnter() override;
    void onExit() override;

private:
};

