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


    // gestion de estados individuales
    void setINIT();

    void setPIZARRA();


};
