#pragma once
#include "ComponentUpdate.h"

class Transform;
class BoxCollider;
class MatchManager;

class EndTurnButton : public ComponentUpdate
{
    
public:
    EndTurnButton(MatchManager::TurnState buttonPropietary);
    ~EndTurnButton();

    void initComponent() override;
    void update() override;

private:

    void ClickButton();

    Transform* tr_;
    BoxCollider* bc_;

    MatchManager* matchManager_;

    MatchManager::TurnState buttonPropietary_;   // Esto es temporal (o no)
};

