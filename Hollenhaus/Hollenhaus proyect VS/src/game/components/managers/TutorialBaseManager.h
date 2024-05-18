#pragma once

#include <../pchs/pch.h>

class Factory;


class TutorialBaseManager : public ComponentUpdate
{
public:
    TutorialBaseManager();
    TutorialBaseManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialBaseManager() override;

    virtual void initComponent();
    void update() override;

    void nextTutorialState();
    void updateTutorialState();
    bool actionEnded();
    void resetEnded();
    virtual void setState();

    void setDeck(ecs::entity_t d) { deck = d; };
    void setNextTurn(ecs::entity_t n) { nextTurn = n; };
    void setCard(ecs::entity_t c) { card = c; };

    //
    ecs::entity_t createPopUp(float x, float y, std::string popup, int convo);
    ecs::entity_t createPopUp(float x, float y, std::string popup, int convo, ecs::entity_t b);

    void setBase(ecs::entity_t b);
    void setTutorial(ecs::entity_t t);
    void setObjs(std::vector<ecs::entity_t> v);
    void setLayers(std::vector<ecs::entity_t> v);
    void addToHand(ecs::entity_t c);


protected:

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


};
