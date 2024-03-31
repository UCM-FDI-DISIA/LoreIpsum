// COMO FUNCIONA EL COMPONENTE:
// Al hacer click en el suelo se guarda toda la info del inicio del movimiento
// En el update se evalua si debe moverse
// (si se ha hecho click, si no se ha llegado al final y si no se ha centrado aun la coor destino guardada al inicio)
// si debe moverse:
// el contador de scroll (unidades a moverse por update): aumenta (izq) o disminuye (der)
// despues de esta evaluacion se ejecuta el movimiento del fondo con su respectiva velocidad

#include "pch.h"
#include "MoveOnClick.h"
#include "../Entity.h"
#include "managers/Manager.h"

#include <cmath>

MoveOnClick::MoveOnClick(float vel) :
	myBoxCollider_(),
	myTransform_(),
	move_(false),
	scrollVel_(vel),
	distance_(),
	movement_(),
	dir_(),
	halfScreen_(sdlutils().width() / 2) {
}

MoveOnClick::~MoveOnClick()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::initComponent()
{
	myTransform_ = ent_->getComponent<Transform>(); // transform del fondo

	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::update()
{
	// ---- Version de Andres y Nieves y Jesus Cristo amen (y jimbo)----
	const float posX = myTransform_->getGlobalPos().getX();

	// ---- MOVE FALSE ----
	// -> si la diferencia entre la pos actual y la inicial es la distancia a recorrer (se ha completado el mov.)
	// -> o cuando llegue a los limites de la ciudad por la derecha Y se pulse en la derecha
	// -> o cuando llegue a los limites de la ciudad por la izquierda Y se pulse en la izquierda
	if  (abs(posX - myPos_.getX()) >= abs(distance_)   || 
		(((posX >= 0) && (mousePos_.getX() < halfScreen_)) ||
		((posX <= BACKGROUND_SIZE) && (mousePos_.getX() >= halfScreen_))))
	{
		move_ = false;
	}
	else if (move_) 
	{
		Vector2D aux = Vector2D(posX + movement_, myTransform_->getGlobalPos().getY());
		myTransform_->setGlobalPos(aux);
	}

#if _DEBUG
	//std::cout << "DISTANCE: " << distance_ << " " << move_ << "\n";
	//std::cout << abs(myTransform_->getGlobalPos().getX() - myPos_.getX()) << "\n";
#endif
}

void MoveOnClick::OnLeftClickDown()
{
	// Si pulsamos en el collider, efectuamos el movimiento
	if (myBoxCollider_->isCursorOver())
	{
		// guardas la posicion del raton en click
		mousePos_ = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

		// posicion del fondo al hacer click
		myPos_ = myTransform_->getGlobalPos();

		// debe moverse al click
		move_ = true;

		// JUGADOR HACIA LA DER, FONDO HACIA LA IZQ
		if (mousePos_.getX() >= halfScreen_)
		{
			dir_ = -1;
			distance_ = mousePos_.getX() - halfScreen_;
		}

		// JUGADOR HACIA LA IZQ, FONDO HACIA LA DER
		else if (mousePos_.getX() < halfScreen_)
		{
			dir_ = 1;
			distance_ = halfScreen_ - mousePos_.getX();
		}

		movement_ = scrollVel_ * dir_;
	}
	else 
	{
		move_ = false;
	}

}