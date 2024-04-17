#pragma once
#include "GameState.h"

class MultiplayerEndGameState
    :public GameState
{
public:
    MultiplayerEndGameState();
    virtual ~MultiplayerEndGameState();


    void refresh() override;
    void update() override;
    void render() const override;


    void onEnter() override;
    void onExit() override;

private:

    void setWindow(int lastWiner);

    void playAgain();
    void changeMaze();
    void exit();


    std::string _background, _text;
};

