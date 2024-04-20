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
    void tutorialActionEnded(Tutorials::Tutorials t, int i);
    void setColliderWall(std::vector<ecs::entity_t> e, ecs::entity_t parent);
    void deactivateColliders(std::vector<ecs::entity_t> n);
    void activateColliders(std::vector<ecs::entity_t> n);
    void activateAllColliders();

    bool hasEnded() { return ended; }
    bool Next() { return next; }
    void startTutorial() { isTutorial = true; }
    void endTutorial() { isTutorial = false; }
    void setCurrentTutorial(Tutorials::Tutorials t) { currtut = t; }
    void setCurrentTutorialState(int t) { currstate = t; }
    void setNextTutorialState(int t) { nextstate = t; }

    Tutorials::Tutorials getTutorial() { return currtut; }
    int getTutorialState() { return currstate; }
    int getNextState() { return nextstate; }

    int nextState() {
        return ++nextstate;
    }

private:

    //
    bool ended;
    bool next;

    int count, cooldown;

    bool isTutorial;

    Tutorials::Tutorials currtut;
    int currstate;
    int nextstate;

    ecs::entity_t colliderWall;
    std::vector<ecs::entity_t> objs;


    void loseCollider(BoxCollider* coll);
    void returnCollider(BoxCollider* coll);

};
