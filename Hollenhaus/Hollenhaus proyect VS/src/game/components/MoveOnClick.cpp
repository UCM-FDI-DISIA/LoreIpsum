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

	feedbackPunto = Instantiate(Vector2D());
	feedbackFlecha = Instantiate(Vector2D());

	feedbackPunto->addComponent<SpriteRenderer>("feedback_circulo");
	feedbackFlecha->addComponent<SpriteRenderer>("feedback_flecha");

	feedbackPunto->setLayer(2);
	feedbackFlecha->setLayer(2);

	flechaTrans = feedbackFlecha->getComponent<Transform>();
	flechaSprite = feedbackFlecha->getComponent<SpriteRenderer>();
	puntoTrans = feedbackPunto->getComponent<Transform>();
	puntoSprite = feedbackPunto->getComponent<SpriteRenderer>();

	puntoTrans->addParent(myTransform_);
	puntoTrans->setGlobalScale(2.5f, 2.5f);
	flechaTrans->addParent(myTransform_);
	flechaTrans->setGlobalScale(2.5f, 2.5f);

	flechaSprite->setOpacity(0);
	puntoSprite->setOpacity(0);

	tweenFade =
		tweeny::from(0)
		.to(255)
		.during(10)
		.via(tweeny::easing::sinusoidalIn);

	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::update()
{
	// ---- Version de Andres y Nieves y Jesus Cristo amen (y jimbo)----
	const float posX = myTransform_->getGlobalPos().getX();
	const float diff = abs(posX - myPos_.getX());

	// ---- MOVE FALSE ----
	// -> si la diferencia entre la pos actual y la inicial es la distancia a recorrer (se ha completado el mov.)
	// -> o cuando llegue a los limites de la ciudad por la derecha Y se pulse en la derecha
	// -> o cuando llegue a los limites de la ciudad por la izquierda Y se pulse en la izquierda
	if (move_ && 
		(diff >= abs(distance_) 
		|| ((posX >= 0 
			&& mousePos_.getX() < halfScreen_) 
		|| (posX <= BACKGROUND_SIZE 
			&& mousePos_.getX() >= halfScreen_))))
	{
		onStop();
	}
	else if (move_)
	{
		auto aux = Vector2D(posX + movement_, myTransform_->getGlobalPos().getY());
		myTransform_->setGlobalPos(aux);
		moveFeedback();
	}

	tweenFade.step(1);
	flechaSprite->setOpacity(tweenFade.peek());
	puntoSprite->setOpacity(tweenFade.peek());

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
	movement_ = 0;
}

void MoveOnClick::moveFeedback()
{
	/// Flecha flotando tween:
	tweenFlecha.loop();
	tweenFlecha.step(1);
	if (tweenFlecha.peek() > 0) // una mierda de manera de 1. saber que devuelve un int valido 2. que no se salga
	{
		Vector2D step(
			flechaTrans->getGlobalPos().getX(),
			tweenFlecha.peek() 
		);
		flechaTrans->setGlobalPos(step);
	}
}

void MoveOnClick::enableFeedback()
{
	flechaTrans->setGlobalPos(
		mousePos_.getX() 
			- puntoSprite->getTexture()->width() / 2 
			+ flechaSprite->getTexture()->width() / 2 - 2,
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

	auto fanY = flechaTrans->getGlobalPos().getY();
	tweenFlecha =
		tweeny::from(fanY - 10)
		.to(fanY + 5)
		.to(fanY - 10)
		.during(30)
		.via(tweeny::easing::sinusoidalInOut);

	tweenFade.seek(0);
	flechaSprite->setOpacity(0);
	puntoSprite->setOpacity(0);
	tweenFade.forward();
}

void MoveOnClick::disableFeedback()
{
	tweenFade.backward();
}
