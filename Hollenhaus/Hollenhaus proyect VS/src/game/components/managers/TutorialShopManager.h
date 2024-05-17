#pragma once

#include <../pchs/pch.h>
#include "TutorialBaseManager.h"
#include "../../TutorialManager.h"



class Factory;


class TutorialShopManager : public TutorialBaseManager
{
public:
    TutorialShopManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialShopManager() override;

    void initComponent() override;
    void update();


    void setState() override;



private:


    // gestion de estados individuales
    void setINIT();

    void setSHOW_MONEY();

    void setSHOW_CARDS();

    void setPURCHASE();



};
