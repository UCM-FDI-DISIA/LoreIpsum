#pragma once

#include "ComponentUpdate.h"
#include "BoxCollider.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "GameStateMachine.h"


class MoveOnClick :
    public ComponentUpdate
{
public:
	MoveOnClick();
	~MoveOnClick();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
private:
	BoxCollider* myBoxCollider;
	Transform* myTransform;

	bool move;
	Vector2D mousePos;
	Vector2D myPos;

	float scrollSpeed = 2.0f;
	float transformer;

};

