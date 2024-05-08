#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include "../../utils/Vector2D.h"
#include <vector>
#include  <functional>
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

    std::vector<std::function<bool(void)>> conditions;

    bool isDraged = false;

    void OnLeftClickDown();

    void OnLeftClickUp();

    bool conditionsValid();

public:

    void addCondition(std::function<bool(void)> condition);
};

