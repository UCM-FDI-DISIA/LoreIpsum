#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"

class Transform :
    public ComponentUpdate
{
public:
    Transform() : parent_(), globalAngle_(0), globalScale_(1, 1), relativeAngle_(0), isChild_(false) {};
    ~Transform() {};

    void update() override;

    // Añade un padre
    //
    void addParent(Transform* p);

    // Quitar un padre
    //
    void removeParent();

    // Posicion global
    //
    Vector2D& getGlobalPos() { return globalPos_; };

    // Escala global
    //
    Vector2D& getGlobalScale() { return globalScale_; };

    // Rotacion global
    //
    float& getGlobalAngle() { return globalAngle_; };

    // Posicion relativa al padre
    //
    Vector2D& getRelativePos() { return relativePos_; };

    // Escala relativa al padre
    //
    Vector2D& getRelativeScale() { return relativeScale_; };

    // Rotacion relativa al padre
    //
    float& getRelativeAngle() { return relativeAngle_; };

    void setGlobalPos(Vector2D& v);

    Transform* getParent() { return parent_; };
    
    Transform& operator+(const Transform& t);
    Transform& operator-(const Transform& t);
    Transform& operator=(const Transform& t);
private:
    Transform* parent_;

    bool isChild_;

    Vector2D globalPos_,
             globalScale_,
             relativePos_,
             relativeScale_,
             vel_;
    float globalAngle_,
          relativeAngle_;
};

