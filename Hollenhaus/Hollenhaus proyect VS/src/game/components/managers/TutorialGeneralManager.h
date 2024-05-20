#pragma once

#include <../pchs/pch.h>
#include "TutorialBaseManager.h"


class Factory;


class TuorialGeneralManager : public TutorialBaseManager
{
public:
    TuorialGeneralManager(ecs::entity_t b, ecs::entity_t t);
    ~TuorialGeneralManager() override;

    void initComponent() override;
    void update();
    void addToHand(ecs::entity_t c);


    void setState() override;



private:


    // gestion de estados individuales
    void setINIT();



};