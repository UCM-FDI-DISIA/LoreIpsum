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

public:

    Vector2D& getCardPos() { return cardPos; };
};

