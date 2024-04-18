#pragma once
#include "GameState.h"

class Factory;
class TutorialManager;

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
    void resetEnded();
    void setState();

    //
    void setBoard();
    void setBaseEntity();
    ecs::entity_t createPopUp(float x, float y, std::string popup, int convo);
    void initTutorial();

    //
    int currentState;       //
    int nextState;          //
    bool ended;             //

    Factory* factory;               //
    ecs::entity_t base;             // entidad para colocar los popups, se va moviendo segun donde los queramos
    ecs::entity_t tutorial;
    ecs::entity_t colliderWallBase;

    int cooldown = 10;
    int count = 0;

    // gestion de estados individuales
    void setINIT();

    void setCARD();

    void setDECK();

    void setDRAWCARD();

    void setCELL();

    void setPLACECARD();

    void setACTION();

    void setACTIONPTS();


};
