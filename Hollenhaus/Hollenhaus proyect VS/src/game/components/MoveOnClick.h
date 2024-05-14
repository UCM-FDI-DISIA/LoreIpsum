#pragma once

//Checkml
#include <game/checkML.h>

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

	bool getDir() const { return faceRight_; };
	void setDir(bool value) { faceRight_ = value; }
	// registra el collider que creas en la escena de la ciudad
	void RegisterCollider(BoxCollider* collider)
	{
		myBoxCollider_ = collider;
	}

	void registerFantasmaTrans(ecs::entity_t entity)
	{
		fanTrans = entity->getComponent<Transform>();
	}

private:
	// collider y transform del fondo
	BoxCollider* myBoxCollider_;
	Transform* myTransform_;

	// debe moverse
	bool shouldMove_;

	// true derecha false izquierda
	bool faceRight_;

	// posicion del raton en clock para saber cuanto moverse
	Vector2D mousePos_;

	// posicion inicial del fondo
	Vector2D initialPos_;

	// velocidad de movimiento de scroll
	float scrollFactor_;

	// distancia entre la posición inicial y la del click
	float absDistance_;

	// Movimiento real
	float movementSpeed_;

	// -1 izquierda, 1 derecha
	int dir_;
	int lastDir_ = 0; // el click anterior al actual

	float halfScreen_;

	/// FEEDBACK
	ecs::entity_t feedbackFlecha;
	ecs::entity_t feedbackPunto;
	Transform* flechaTrans;
	Transform* puntoTrans;
	SpriteRenderer* flechaSprite;
	SpriteRenderer* puntoSprite;
	tweeny::tween<float> tweenFlecha; // la flecha flota
	tweeny::tween<int> tweenFade; // fade in/out del feedback
	tweeny::tween<float> tweenMovement;

	void onStart();
	void onStop();
	void moveFeedback();
	void enableFeedback();
	void disableFeedback();
	void enableLerp();
	void disableLerp();

	Transform* fanTrans;
	tweeny::tween<float> tweenFantasmiko;

	template<typename T>
	tweeny::tween<T> resetTween(T, T);
};


