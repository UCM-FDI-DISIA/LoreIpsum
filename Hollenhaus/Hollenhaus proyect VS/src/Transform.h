#pragma once
#include "game/ComponentUpdate.h"
#include "utils/Vector2D.h"
class Transform :
    public ComponentUpdate
{
public:
    Transform() : parent_(), angle_(), isChild_(false) {};
    ~Transform() {
        delete parent_;
        parent_ = nullptr;
    };

    void update() override;

    // Añadir un padre
    void addParent(Transform* p);
    // Getters
    Vector2D getPos() { 
        if (isChild_)
            return pos_ + parent_->pos_;
        else
            return pos_;
    };
    Vector2D getScale() { return scale_; };
    float getAngle() { return angle_; };

    Transform& operator+(const Transform& t);
    Transform& operator-(const Transform& t);
    Transform& operator=(const Transform& t);
private:
    Transform* parent_;
    bool isChild_;

    Vector2D pos_,
             vel_,
             scale_;
    float angle_;
};

