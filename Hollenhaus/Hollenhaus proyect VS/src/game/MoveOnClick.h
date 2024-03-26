#pragma once

#include "ComponentUpdate.h"
#include "BoxCollider.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "GameStateMachine.h"

class MoveOnClick : public ComponentUpdate
{
public:
	MoveOnClick();
	~MoveOnClick();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();

	// registra el collider que creas en la escena de la ciudad
	void RegisterCollider(BoxCollider *sceneColliderSuelo)
	{ 
		myBoxCollider = sceneColliderSuelo;
	}

private:
	// collider y transform del fondo
	BoxCollider* myBoxCollider;
	Transform* myTransform;
	int const BACKGROUND_SIZE = -2049;

	// debe moverse
	bool move;

	// posicion del raton en clock para saber cuanto moverse
	Vector2D mousePos;

	// posicion inicial del fondo
	Vector2D myPos; 

	// pixeles a mover en cada update que haya movimiento
	float scrollCounter;

	// velocidad de movimiento de scroll
	float scrollVel = 2;

	// Coordenada x del left top de la imagen de fondo
	//		Ha de ser actualizada en cada update en el que deba moverse hasta
	//		que se haya movido exactamente la distanceToMove
	Vector2D ltBackroundCoor;

	// Distancia final que debe moverse el fondo
	float distanceToMove;
	float distanceNow;

	// -1 izquierda 1 derecha
	int direccion;

	// Mitad de la pantalla
	float halfScreen = sdlutils().width() / 2;

};