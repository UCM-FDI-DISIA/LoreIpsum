#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class Factory;

class LuisState :
    public GameState
{
public:
    LuisState();
    virtual ~LuisState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void setKey() override;
    void setJ2(std::string rival) override;

private:
    std::array<ecs::entity_t, 4>  createPointsJ1();
    std::array<ecs::entity_t, 4> createPointsJ2();
    Factory* factory = nullptr;

    ecs::entity_t key_;
    Transform* keyTr_;
    std::list<BoxCollider*> colliders_;
    bool moveKey_;
    std::string j2_;
};

