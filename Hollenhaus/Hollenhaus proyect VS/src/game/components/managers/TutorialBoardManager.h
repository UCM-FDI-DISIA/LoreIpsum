#pragma once

#include "../../pch.h"

class Factory;


class TutorialBoardManager : public ComponentUpdate
{
public:
    TutorialBoardManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialBoardManager() override;

    void initComponent() override;
    void update() override;

    void nextTutorialState();
    void updateTutorialState();
    bool actionEnded();
    void resetEnded();
    void setState();

    void setDeck(ecs::entity_t d) { deck = d; };
    void setNextTurn(ecs::entity_t n) { nextTurn = n; };
    void setCard(ecs::entity_t c) { card = c; };

    //
    ecs::entity_t createPopUp(float x, float y, std::string popup, int convo);
    void setBase(ecs::entity_t b);
    void setTutorial(ecs::entity_t t);
    void setObjs(std::vector<ecs::entity_t> v);


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

    ecs::entity_t deck;
    ecs::entity_t nextTurn;
    ecs::entity_t card;

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

    void setNEXTTURN();
    

};
