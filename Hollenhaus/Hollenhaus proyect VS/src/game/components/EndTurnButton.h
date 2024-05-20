#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include "ImageWithFrames.h"
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

    void setMultiplayer(bool b);

private:

    void ClickButton();

    Transform* tr_;
    BoxCollider* bc_;
    ImageWithFrames* iwf_;

    MatchManager* matchManager_;

    Turns::State buttonPropietary_;   // Esto es temporal (o no)

    Turns::State myMultiplayerTurn; 

    bool activeIA = false;

    bool activeMultiplayer = false;
};

