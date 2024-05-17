#pragma once

#include <../pchs/pch.h>
#include "TutorialBaseManager.h"


class Factory;


class TutorialCityManager : public TutorialBaseManager
{
public:
    TutorialCityManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialCityManager() override;

    void initComponent() override;
    void update();


    void setState() override;



private:

    // NO ESTA HECHO EL JSON AUN !!!

    // gestion de estados individuales
    void setINIT();

    void setINTERACTION();

    void setMOVE();


};
