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
	Vector2D myPos; //posicion inicial de la entidad (fondo)

	float scrollSpeed;
	Vector2D movement;
	float moveTo;

	float halfScreen = sdlutils().width() / 2;

};

