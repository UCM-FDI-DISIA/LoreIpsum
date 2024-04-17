#pragma once
#include "GameState.h"

//forward declaration
class TextComponent;


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

    void swapColor(TextComponent* tc, bool b);

    std::string _background, _text;
};

