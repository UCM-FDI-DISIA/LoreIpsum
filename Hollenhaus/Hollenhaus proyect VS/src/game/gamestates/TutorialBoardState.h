#pragma once
#include "GameState.h"

class TutorialBoardState :
    public GameState
{
public:
    TutorialBoardState();
    virtual ~TutorialBoardState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:

    //
    void nextTutorialState();
    void updateTutorialState();

    //
    void createPopUp();

    //
    enum Tutorial {
        INIT,
        CARD,
        DECK,
        CELL,
        ACTION,
        ACTION_PTS
    };

    //
    int currentState;
    int nextState;
};
