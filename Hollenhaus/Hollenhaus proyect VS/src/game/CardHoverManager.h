#pragma once
#include "ComponentUpdate.h"

class Transform;

#include "../utils/Vector2D.h"

class CardHoverManager :
    public ComponentUpdate
{
public:
    CardHoverManager();
    ~CardHoverManager();

    void initComponent() override;
    void update() override;

private:

    Transform* hoverTransform = nullptr;

    float scaleMultiplier = 1.25f;

    int layerOnHover = 5;
    int previousLayer;

    Vector2D previousScale;

};

