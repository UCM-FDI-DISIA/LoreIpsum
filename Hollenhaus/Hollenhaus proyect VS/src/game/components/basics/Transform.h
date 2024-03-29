#pragma once
#include "../ComponentUpdate.h"

class Transform :
    public ComponentUpdate
{
public:
    Transform()
	: parent_(nullptr), isChild_(false), globalScale_(1, 1), relativeScale_(1,1),
	  globalAngle_(0), relativeAngle_(0), layerToIncrease(1) {};
    ~Transform(){};

    void update() override;

    void increaseLayer(int);

    void setLayerIncrementalInHierarchy(int layer);

    // Aniade un padre
    //
    void addParent(Transform* p);

    // Quitar un padre
    //
    void removeParent();

    // Matar hijos
    void killChilds();

    std::list<Transform*> getChildren();

    // Posicion global
    // He quitao la referencia
    Vector2D getGlobalPos();

    // Escala global
    //
    Vector2D getGlobalScale();
    //void setGlobalScale(float x, float y) { globalScale_ = Vector2D(x,y); }

    // Rotacion global
    //
    float& getGlobalAngle();

    // Posicion relativa al padre
    //
    Vector2D& getRelativePos();

    // Escala relativa al padre
    //
    Vector2D& getRelativeScale();

    // Rotacion relativa al padre
    //
    float& getRelativeAngle();

    void setGlobalPos(Vector2D& v);
    void setGlobalAngle(float);
    void setGlobalScale(Vector2D);
    void setGlobalScale(float x, float y);

    Transform* getParent();
    
    Transform& operator+(const Transform& t);
    Transform& operator-(const Transform& t);
    Transform& operator=(const Transform& t);
private:
    void addChild(Transform* c);
    void removeChild(Transform* c);

    Transform* parent_;
    std::list<Transform*> children_;

    bool isChild_;

    Vector2D globalPos_,
             globalScale_,
             relativePos_,
             relativeScale_,
             vel_;
    float globalAngle_,
          relativeAngle_;

    int layerToIncrease;
};

