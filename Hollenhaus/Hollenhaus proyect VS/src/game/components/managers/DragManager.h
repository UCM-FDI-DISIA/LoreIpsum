#pragma once
#include "../ComponentUpdate.h"



class Transform;
class BoardManager;
class Vector2D;
class DropDetector;

class DragManager :
    public ComponentUpdate
{
public:
    DragManager();
    ~DragManager();

    void initComponent() override;
    void update() override;

    void setBoardManager(BoardManager* _boardManager) { boardManager = _boardManager; }
    void updateFeedback();
    
    bool isDraggable() const { return draggable; }
    void setDraggable(bool value) { draggable = value; }
private:
    
    Transform* dragTransform;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;
    Vector2D initialTransformPosWithOffSet;

    //Cosas de feedback
    ecs::entity_t   lastCell = nullptr;

    void OnLeftClickDown();
    void OnLeftClickUp();
    void putCardAnimation(DropDetector* cell);
    bool CardOnHand(ecs::entity_t card);
    bool CardIsOfCurrentPlayer(ecs::entity_t card);
    bool enoughPoints(ecs::entity_t card);
    void putCardOnBoard(ecs::entity_t card,DropDetector* cell);
    void colorEffects(ecs::entity_t drop);

    BoardManager* boardManager;
	bool draggable = true;

};

