#pragma once
//Checkml
#include <game/checkML.h>
#include "ComponentUpdate.h"

class Transform;
class Vector2D;

class SolDragComponent :
    public ComponentUpdate
{
public:
    SolDragComponent();
    ~SolDragComponent();

    void initComponent() override;
    void update() override;

private:

    

    Transform* dragTransform;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;
    Vector2D initialTransformPosWithOffSet;

    void OnLeftClickDown();
    void OnLeftClickUp();

};