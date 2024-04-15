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

    bool hasEnded() { return ended; }

private:

    bool ended;

};
