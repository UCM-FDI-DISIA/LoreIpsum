#pragma once
#include "GameState.h"

class Factory;

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
    bool actionEnded();

    //
    void setBoard();
    void createPopUp(float x, float y, std::string popup);

    //
    enum Tutorial {
        NONE,
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
    bool ended;

    Factory* factory;

    // gestion de estados individuales
    void setINIT();

    void setCARD();

    void setDECK();

};
