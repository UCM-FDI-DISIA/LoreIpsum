#pragma once
#include "ComponentUpdate.h"
#include "managers/MatchManager.h"

class Transform;
class BoxCollider;


class EndTurnButton : public ComponentUpdate
{
    
public:
    EndTurnButton(){}
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

