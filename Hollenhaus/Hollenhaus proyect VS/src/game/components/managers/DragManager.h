#pragma once
#include "../ComponentUpdate.h"



class Transform;
class BoardManager;
class Vector2D;

class DragManager :
    public ComponentUpdate
{
public:
    DragManager();
    ~DragManager();

    void initComponent() override;
    void update() override;

    void setBoardManager(BoardManager* _boardManager) { boardManager = _boardManager; }

private:
    
    Transform* dragTransform;

    Vector2D initialMousePos;
    Vector2D initialTransformPos;

    void OnLeftClickDown();

    void OnLeftClickUp();

    BoardManager* boardManager;

};

