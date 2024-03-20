#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"

class SpriteRenderer;
class BoxCollider;
class Transform;

class Vector2D;

class CardOnHover :
    public ComponentUpdate
{

public:
    CardOnHover();
    ~CardOnHover();

    void initComponent() override;
    void update() override;


private:

    int layerOnHover;
    int previousLayer;


    float scaleMultiplier = 2.5f;
    Vector2D scaleOnHover; 
    Vector2D previousScale;

    SpriteRenderer* mySpriteRenderer;
    BoxCollider* myBoxCollider;
    Transform* myTransform;
};

