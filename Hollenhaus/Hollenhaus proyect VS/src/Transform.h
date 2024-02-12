#pragma once
#include "game/Component.h"
#include "utils/Vector2D.h"
class Transform :
    public Component
{
public:
    Transform() : parent() {
        if (parent != nullptr) parent;
    };
    ~Transform() {};

    Transform& operator+(const Transform& t);
private:
    Transform* parent;

    Vector2D pos,
             scale;
    float angle;
};

