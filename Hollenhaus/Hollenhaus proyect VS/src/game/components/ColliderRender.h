#pragma once
#include "ComponentRender.h"

class Transform;
class BoxCollider;


class ColliderRender :
    public ComponentRender
{
public:
    ColliderRender();
    ~ColliderRender();

    void initComponent() override;

    void render() const;

private:

    Transform* myTransform;
    BoxCollider* myBoxCollider;
    

};

