#pragma once
#include "pch.h"


class TutorialManager : public ComponentUpdate
{
public:
    TutorialManager();
    ~TutorialManager() override;

    void initComponent() override;
    void update() override;


    void actionEnded();
    void resetAction();
    void wait();

    bool hasEnded() { return ended; }

private:

    bool ended;

    int count, cooldown;

};
