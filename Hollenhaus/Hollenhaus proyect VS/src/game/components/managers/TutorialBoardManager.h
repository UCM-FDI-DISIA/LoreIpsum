#pragma once

#include "../../pch.h"

class Factory;


class TutorialBoardManager : public ComponentUpdate
{
public:
    TutorialBoardManager();
    ~TutorialBoardManager() override;

    void initComponent() override;
    void update() override;

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
    void setBase(ecs::entity_t b) { base = b; };
    void setTutorial(ecs::entity_t t) { tutorial = t; };

private:

    int currentState;       //
    int nextState;          //
    bool ended;             //

    Factory* factory;               //
    ecs::entity_t base;             // entidad para colocar los popups, se va moviendo segun donde los queramos
    ecs::entity_t tutorial;
    ecs::entity_t colliderWallBase;
    //ecs::entity_t* tutorial;

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
