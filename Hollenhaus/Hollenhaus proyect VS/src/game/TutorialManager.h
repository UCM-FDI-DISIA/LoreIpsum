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
    void tutorialActionEnded();

    bool hasEnded() { return ended; }
    bool Next() { return next; }
    void startTutorial() { isTutorial = true; }
    void endTutorial() { isTutorial = false; }

private:

    //
    bool ended;
    bool next;

    int count, cooldown;

    bool isTutorial;

};
