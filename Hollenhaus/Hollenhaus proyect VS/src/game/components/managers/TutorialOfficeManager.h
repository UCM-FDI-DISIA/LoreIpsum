#pragma once

#include <../pchs/pch.h>
#include "TutorialBaseManager.h"


class Factory;


class TutorialOfficeManager : public TutorialBaseManager
{
public:
    TutorialOfficeManager(ecs::entity_t b, ecs::entity_t t);
    ~TutorialOfficeManager() override;

    void initComponent() override;
    void update();


    void setState() override;



private:

    // NO ESTA HECHO EL JSON AUN !!!

    // gestion de estados individuales
    void setINIT();

    void setPHONE();

    void setPIZARRA();


};
