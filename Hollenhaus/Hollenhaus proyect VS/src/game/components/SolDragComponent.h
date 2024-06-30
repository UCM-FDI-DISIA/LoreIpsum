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

    int nCardsUncovered;

    Transform* dragTransform;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;
    Vector2D initialTransformPosWithOffSet;

    void OnLeftClickDown();
    void OnLeftClickUp();

    void makeTopCardsChildren(Transform* t);
    void resetParent(Transform* t);

    void setLayerTopCards(Transform* t, int layer);

    void resetLayerTopCards(Transform* t, int layer);

    void showLeftCards(ecs::entity_t card, std::vector<ecs::entity_t> c);


};