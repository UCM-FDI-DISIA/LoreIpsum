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
    void wait(std::function<void()> callback);

    bool hasEnded() { return ended; }
    bool Next() { return next; }

private:

    //
    bool ended;
    bool next;

    int count, cooldown;

};
