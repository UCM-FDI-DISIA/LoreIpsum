#pragma once
#include "ComponentUpdate.h"

#include "../utils/Vector2D.h"

class Transform;


class DragManager :
    public ComponentUpdate
{
public:
    DragManager();
    ~DragManager();

    void initComponent() override;
    void update() override;

private:
    
    Transform* dragTransform;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;

    void OnLeftClickDown();

    void OnLeftClickUp();

};

