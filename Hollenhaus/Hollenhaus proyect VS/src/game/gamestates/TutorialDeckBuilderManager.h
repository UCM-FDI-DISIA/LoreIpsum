#pragma once

#include <../pchs/pch.h>
#include "TutorialBaseManager.h"


class Factory;


class TutorialDeckBuilderManager : public TutorialBaseManager
{
public:
    TutorialDeckBuilderManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialDeckBuilderManager() override;

    void initComponent() override;
    void update();
    void addToHand(ecs::entity_t c);


    void setState() override;



private:

    int currentState;       //
    int nextState;          //
    bool ended;             //
    bool checked;

    Factory* factory;               //
    ecs::entity_t base;             // entidad para colocar los popups, se va moviendo segun donde los queramos
    ecs::entity_t tutorial;
    ecs::entity_t colliderWallBase;
    std::vector<ecs::entity_t> objs;
    ecs::entity_t image;

    ecs::entity_t deck;
    ecs::entity_t nextTurn;
    ecs::entity_t card;
    std::vector<ecs::entity_t> hand;

    int cooldown = 10;
    int count = 0;

    // gestion de estados individuales
    void setINIT();

    void setCARD();

    void setCARDPOINTS();

    void setCARDCOST();

    void setCARDIMAGE();

    void setDECK();

    void setDRAWCARD();

    void setCELL();

    void setPLACECARD();

    void setPOINTS();

    void setACTION();

    void setACTIONPTS();

    void setNEXTTURN();

    void setPRESSNEXTTURN();

    void setAI_TURN();

    void setNEXTCARD1();

    void setEFFECTS1();

    void setENDTUTORIAL();

    void setFREEDOM();


};
