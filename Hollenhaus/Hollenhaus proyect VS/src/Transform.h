#pragma once
#include "game/ComponentUpdate.h"
#include "utils/Vector2D.h"
class Transform :
    public ComponentUpdate
{
public:
    Transform() : parent_(), globalAngle_(0), relativeAngle_(0), isChild_(false) {};
    ~Transform() {
        delete parent_;
        parent_ = nullptr;
    };

    void update() override;

    // LOGICA DE JERARQUIA
    // Añadir un padre
    void addParent(Transform* p);
    // Quitar padre
    void removeParent();

    // GETTERS
    // Globales
    Vector2D& getGlobalPos() { return globalPos_; };
    Vector2D& getGlobalScale() { return globalScale_; };
    float& getGlobalAngle() { return globalAngle_; };
    // Relativos
    Vector2D& getRelativePos() { return relativePos_; };
    Vector2D& getRealativeScale() { return relativeScale_; };
    float& getRelativeAngle() { return relativeAngle_; };
    
    // OPERADORES
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

