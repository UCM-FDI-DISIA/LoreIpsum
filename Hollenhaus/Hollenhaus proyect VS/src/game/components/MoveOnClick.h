#pragma once

#include "ComponentUpdate.h"
#include "../components/basics/BoxCollider.h"

class Vector2D;

constexpr int BACKGROUND_SIZE = -2049;

class MoveOnClick : public ComponentUpdate
{
public:
	MoveOnClick(float vel);
	~MoveOnClick() override;

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();

	bool getDir() { return faceTo_; };

	// registra el collider que creas en la escena de la ciudad
	void RegisterCollider(BoxCollider* collider)
	{
		myBoxCollider_ = collider;
	}

private:
	// collider y transform del fondo
	BoxCollider* myBoxCollider_;
	Transform* myTransform_;

	// debe moverse
	bool move_;

	// true derecha false izquierda
	bool faceTo_;

	// posicion del raton en clock para saber cuanto moverse
	Vector2D mousePos_;

	// posicion inicial del fondo
	Vector2D myPos_;

	// velocidad de movimiento de scroll
	float scrollVel_;

	float distance_;

	// Movimiento real
	float movement_;

	// -1 izquierda, 1 derecha
	int dir_;

	float halfScreen_;
};