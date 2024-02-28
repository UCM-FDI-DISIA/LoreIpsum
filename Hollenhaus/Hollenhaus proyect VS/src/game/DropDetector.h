#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"



class DropDetector :
    public ComponentUpdate
{
public:

    DropDetector();
    ~DropDetector();

    void initComponent() override;
    void update() override;

private:


    Vector2D cardPos;

    Vector2D boardPos;

public:

    Vector2D& getCardPos() { return cardPos; };

    Vector2D& getBoardPos() { return boardPos; };
};

