#pragma once
#include "ComponentUpdate.h"
#include "managers/MatchManager.h"

class Transform;
class BoxCollider;


class EndTurnButton : public ComponentUpdate
{
    
public:
    EndTurnButton(){}
    EndTurnButton(Turns::State buttonPropietary);
    ~EndTurnButton();

    void initComponent() override;
    void update() override;

    //para decir que vamos a jugar contra la IA
    void setIA(bool b);

private:

    void ClickButton();

    Transform* tr_;
    BoxCollider* bc_;

    MatchManager* matchManager_;

    Turns::State buttonPropietary_;   // Esto es temporal (o no)

    bool activeIA = false;
};

