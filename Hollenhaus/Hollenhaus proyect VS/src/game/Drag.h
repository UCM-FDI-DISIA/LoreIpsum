#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"

class Transform;
class BoxCollider;

class Drag :
    public ComponentUpdate
{
public:
    Drag();
    ~Drag();

    void initComponent() override;

    void update() override;

private:

    Transform* myTransform;

    BoxCollider* myBoxCollider;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;


    bool isDraged = false;

    void OnLeftClickDown();

    void OnLeftClickUp();
};

