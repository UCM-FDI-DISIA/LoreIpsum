#pragma once
#include "ComponentUpdate.h"

class Transform;
class Vector2D;

class CardHoverManager :
    public ComponentUpdate
{
public:
    CardHoverManager();
    ~CardHoverManager();

    void initComponent() override;
    void update() override;

private:

    Transform* hoverTransform;

    float scaleMultiplier;

    int layerOnHover;
    int previousLayer;


};

