// COMO FUNCIONA EL COMPONENTE:
// Al hacer click en el suelo se guarda toda la info del inicio del movimiento
// En el update se evalua si debe moverse
// (si se ha hecho click, si no se ha llegado al final y si no se ha centrado aun la coor destino guardada al inicio)
// si debe moverse:
// el contador de scroll (unidades a moverse por update): aumenta (izq) o disminuye (der)
// despues de esta evaluacion se ejecuta el movimiento del fondo con su respectiva velocidad

#include "pch.h"
#include "MoveOnClick.h"
#include <cmath>

constexpr Uint32 FEEDBACK_PADDING = 60;

MoveOnClick::MoveOnClick(float vel) :
	myBoxCollider_(),
	myTransform_(),
	move_(false),
	faceTo_(),
	scrollVel_(vel),
	distance_(),
	movement_(),
	dir_(),
	halfScreen_(sdlutils().width() / 2)
{
}

MoveOnClick::~MoveOnClick()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::initComponent()
{
	myTransform_ = ent_->getComponent<Transform>(); // transform del fondo

	feedbackFlecha = Instantiate(Vector2D());
	feedbackPunto = Instantiate(Vector2D());
	feedbackFlecha->addComponent<SpriteRenderer>("feedback_flecha")->enable(false);
	feedbackPunto->addComponent<SpriteRenderer>("feedback_circulo")->enable(false);
	feedbackFlecha->setLayer(2);
	feedbackPunto->setLayer(2);
	flechaTrans = feedbackFlecha->getComponent<Transform>();
	puntoTrans = feedbackPunto->getComponent<Transform>();
	/*flechaTrans->addParent(myTransform_); esto hace que se comporte muy raro
	puntoTrans->addParent(myTransform_);*/

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
	if (abs(posX - myPos_.getX()) >= abs(distance_) ||
		(((posX >= 0) && (mousePos_.getX() < halfScreen_)) ||
			((posX <= BACKGROUND_SIZE) && (mousePos_.getX() >= halfScreen_))))
	{
		onStop();
	}
	else if (move_)
	{
		auto aux = Vector2D(posX + movement_, myTransform_->getGlobalPos().getY());
		myTransform_->setGlobalPos(aux);
		moveFeedback();
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
			faceTo_ = true;
		}

		// JUGADOR HACIA LA IZQ, FONDO HACIA LA DER
		else if (mousePos_.getX() < halfScreen_)
		{
			dir_ = 1;
			distance_ = halfScreen_ - mousePos_.getX();
			faceTo_ = false;
		}

		movement_ = scrollVel_ * dir_;

		enableFeedback();
	}
	else
	{
		onStop();
	}
}

void MoveOnClick::onStop()
{
	disableFeedback();
	move_ = false;
}

void MoveOnClick::moveFeedback()
{
	tweenMovimiento.step(1);
	if (tweenMovimiento.peek() > 0)
	{
		flechaTrans->setGlobalPos(
			tweenMovimiento.peek(),
			flechaTrans->getGlobalPos().getY()
		);
		puntoTrans->setGlobalPos(
			tweenMovimiento.peek(),
			puntoTrans->getGlobalPos().getY()
		);
	}
}

void MoveOnClick::enableFeedback()
{
	const auto flechaSprite = feedbackFlecha->getComponent<SpriteRenderer>();
	const auto puntoSprite = feedbackPunto->getComponent<SpriteRenderer>();

	flechaTrans->setGlobalPos(
		mousePos_.getX() - flechaSprite->getTexture()->width() / 2,
		sdlutils().height()
			- FEEDBACK_PADDING
			- flechaSprite->getTexture()->height() / 2
			- puntoSprite->getTexture()->height() * 2
	);
	puntoTrans->setGlobalPos(
		mousePos_.getX() - puntoSprite->getTexture()->width() / 2,
		sdlutils().height()
			- FEEDBACK_PADDING
			- puntoSprite->getTexture()->height() / 2
	);

	flechaSprite->enable(true);
	puntoSprite->enable(true);

	auto x = mousePos_.getX();
	tweenMovimiento =
		tweeny::from(x)
		.to(sdlutils().width()/2)
		.during(60);
	tweenMovimiento.forward();
		//.via(tweeny::easing::sinusoidalInOut);
}

void MoveOnClick::disableFeedback()
{
	const auto flechaSprite = feedbackFlecha->getComponent<SpriteRenderer>();
	const auto puntoSprite = feedbackPunto->getComponent<SpriteRenderer>();
	flechaSprite->enable(false);
	puntoSprite->enable(false);
}
