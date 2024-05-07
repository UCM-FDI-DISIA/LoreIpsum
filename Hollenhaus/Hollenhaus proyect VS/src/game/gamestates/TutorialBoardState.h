#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class Factory;
class TutorialManager;

class TutorialBoardState :
    public GameState
{
public:
    TutorialBoardState();
    virtual ~TutorialBoardState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

private:

    //
    void setBoard();
    void setBaseEntity();
    void initTutorial();

    Factory* factory = nullptr;               //
    ecs::entity_t base = nullptr;             // entidad para colocar los popups, se va moviendo segun donde los queramos
    ecs::entity_t tutorial = nullptr;
    ecs::entity_t colliderWallBase = nullptr;

    //TutorialBoardManager* tutorialManager_;

    std::vector<ecs::entity_t> objs;

    int cooldown = 10;
    int count = 0;



};
