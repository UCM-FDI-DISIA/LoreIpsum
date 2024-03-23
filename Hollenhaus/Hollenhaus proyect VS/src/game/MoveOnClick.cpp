#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"

MoveOnClick::MoveOnClick()
{
}

MoveOnClick::~MoveOnClick()
{
	// se suscribe al evento de click izq
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::initComponent()
{
	myBoxCollider = ent_->getComponent<BoxCollider>(); // collider del fondo
	myTransform = ent_->getComponent<Transform>();	   // transform del fondo
	
	move = false; // inicializa move a false

	// se inicializa el movement al left top del fondo (independientemente de la pantalla, solo de la imagen)
	ltBackroundCoor.setX(myTransform->getGlobalPos().getX());

	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::update()
{
	// ---- MOVE FALSE ----
	// -> si la coordenda x del lt del fondo coincide con el distanceToMove (se ha centrado)
	// -> o cuando llegue a los limites de la ciudad por la derecha y se pulse en la derecha
	// -> o cuando llegue a los limites de la ciudad por la izquierda y se pulse en la izquierda
	if ((ltBackroundCoor.getX() == distanceToMove) ||
		((ltBackroundCoor.getX() >= 0) && (mousePos.getX() < halfScreen)) ||
		((ltBackroundCoor.getX() <= BACKGROUND_SIZE) && (mousePos.getX() >= halfScreen)))
	{ move = false; }

	// ---- MOVE TRUE ----
	// -> si debe moverse
	if (move)
	{
		// JUGADOR HACIA LA DER, FONDO HACIA LA IZQ
		if (mousePos.getX() >= halfScreen)
		{
			scrollCounter--;
		}

		// JUGADOR HACIA LA IZQ, FONDO HACIA LA DER
		else if (mousePos.getX() < halfScreen)
		{
			scrollCounter++;
		}

		ltBackroundCoor.setX(myPos.getX() + scrollCounter * scrollVel);

		myTransform->setGlobalPos(ltBackroundCoor);
	}
}

void MoveOnClick::OnLeftClickDown()
{
	// guardas la posicion del raton en click
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	// posicion del fondo al hacer click
	myPos = myTransform->getGlobalPos();

	// Si pulsamos en el collider, efectuamos el movimiento
	if (myBoxCollider->isCursorOver()){

		// debe moverse al click
		move = true;

		// resetea la distancia a moverse en cada update que hay movimiento
		scrollCounter = 1.0f;

		// guardar en moveTo = (left top de la imagen en ese momento) - (donde hagas click - (mitad de la pantalla))
		// le resta al left top de la imagen en ese momento la distancia entre el sitio a moverse y la mitad de la pantalla
		distanceToMove = myTransform->getGlobalPos().getX() - (mousePos.getX() - halfScreen);
	}
}