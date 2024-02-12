#pragma once
#include "game/ComponentUpdate.h"
#include "utils/Vector2D.h"
class Transform :
    public ComponentUpdate
{
public:
    Transform() : parent(), angle() {
        if (parent != nullptr);
    };
    ~Transform() {};

    Transform& operator+(const Transform& t);
    Transform& operator=(const Transform& t);
private:
    Transform* parent;

    Vector2D pos,
             scale;
    float angle;
};

