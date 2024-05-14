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
