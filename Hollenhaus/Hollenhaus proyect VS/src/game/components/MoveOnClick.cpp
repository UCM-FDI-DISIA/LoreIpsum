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

constexpr Uint32 FEEDBACK_PADDING = 60,
                 ACC_DURATION = 10;
constexpr int MOVE_OFFSET = 10;
                 

MoveOnClick::MoveOnClick(float vel) :
	myBoxCollider_(),
	myTransform_(),
	shouldMove_(false),
	faceRight_(),
	scrollFactor_(vel),
	absDistance_(),
	movementSpeed_(),
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

	tweenMovement =
		tweeny::from(0.0f)
		.to(scrollFactor_ * dir_)
		.during(ACC_DURATION)
		.via(tweeny::easing::linear);

	tweenFantasmiko =
		tweeny::from(halfScreen_ - 50.0f)
		.to(halfScreen_ - 50.0f + MOVE_OFFSET * dir_)
		.during(ACC_DURATION)
		.via(tweeny::easing::linear);


	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
}

void MoveOnClick::update()
{
	// ---- Version de Andres y Nieves y Jesus Cristo amen (y jimbo)----
	const float posX = myTransform_->getGlobalPos().getX();
	const float diff = abs(posX - initialPos_.getX());

	/// PROGRESO DE LOS TWEENS DE MOVIMIENTO
	tweenMovement.step(1);
	tweenFantasmiko.step(1);

	// ---- MOVE FALSE ----
	// -> si la diferencia entre la pos actual y la inicial es la distancia a recorrer (se ha completado el mov.)
	// -> o cuando llegue a los limites de la ciudad por la derecha Y se pulse en la derecha
	// -> o cuando llegue a los limites de la ciudad por la izquierda Y se pulse en la izquierda
	if (shouldMove_ &&
		(diff >= absDistance_
			|| ((posX >= 0
					&& mousePos_.getX() < halfScreen_)
				|| (posX <= BACKGROUND_SIZE
					&& mousePos_.getX() >= halfScreen_))))
	{
		onStop();
	}
	else if (shouldMove_)
		moveFeedback(); // TWEEN DEL FEEDBACK

	/// MOVIMIENTO DEL FONDO
	movementSpeed_ = tweenMovement.peek();
	auto aux = Vector2D(posX + movementSpeed_, myTransform_->getGlobalPos().getY());
	myTransform_->setGlobalPos(aux);

	/// TWEEN DEL FANTASMA
	fanTrans->setGlobalPos(
		tweenFantasmiko.peek(),
		fanTrans->getGlobalPos().getY()
	);

	/// TWEEN DE LA OPACIDAD DEL FEEDBACK
	tweenFade.step(1);
	flechaSprite->setOpacity(tweenFade.peek());
	puntoSprite->setOpacity(tweenFade.peek());

#if _DEBUG
	//std::cout << "DISTANCE: " << absDistance_ << " " << shouldMove_ << "\n";
	//std::cout << abs(myTransform_->getGlobalPos().getX() - initialPos_.getX()) << "\n";
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
		initialPos_ = myTransform_->getGlobalPos();

		// debe moverse al click
		shouldMove_ = true;

		// JUGADOR HACIA LA DER, FONDO HACIA LA IZQ
		if (mousePos_.getX() >= halfScreen_)
		{
			dir_ = -1;
			absDistance_ = mousePos_.getX() - halfScreen_;
			faceRight_ = true;
		}

		// JUGADOR HACIA LA IZQ, FONDO HACIA LA DER
		else if (mousePos_.getX() < halfScreen_)
		{
			dir_ = 1;
			absDistance_ = halfScreen_ - mousePos_.getX();
			faceRight_ = false;
		}

		//movementSpeed_ = scrollFactor_ * dir_;

		enableLerp();
		enableFeedback();
	}
	else onStop();
}

void MoveOnClick::onStop()
{
	disableFeedback();
	shouldMove_ = false;
	disableLerp();
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

void MoveOnClick::enableLerp()
{
	/// DEL PROPIO FONDO
	tweenMovement =
		tweeny::from(0.0f)
		.to(scrollFactor_ * dir_)
		.during(ACC_DURATION)
		.via(tweeny::easing::linear);
	if (movementSpeed_ <= 0)
	{
		tweenMovement.seek(0);
		movementSpeed_ = 0;
	}
	tweenMovement.forward();

	/// DEL FANTASMIKO
	assert (fanTrans != nullptr);
	auto fanX = fanTrans->getGlobalPos().getX();
	tweenFantasmiko =
		tweeny::from(halfScreen_ - 50.0f)
		.to(halfScreen_ - 50.0f + MOVE_OFFSET * dir_)
		.during(ACC_DURATION)
		.via(tweeny::easing::linear);

	if (movementSpeed_ <= 0)
		tweenFantasmiko.seek(0);
	tweenFantasmiko.forward();
}

void MoveOnClick::disableLerp()
{
	tweenMovement.backward(); // del fondo
	tweenFantasmiko.backward();
}
