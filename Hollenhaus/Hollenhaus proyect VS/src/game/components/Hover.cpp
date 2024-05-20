#include "../pchs/pch.h"
#include "Hover.h"

#include "basics/TextComponent.h"

constexpr int EFFECT_OFFSET_X = 25,
              EFFECT_OFFSET_Y = 20;

void Hover::initComponent()
{
	tr = getEntity()->getComponent<Transform>();
	spr = getEntity()->getComponent<SpriteRenderer>();

	assert(tr != nullptr);
	assert(spr != nullptr);

	//iniScale = tr->getGlobalScale();
	iniPos = tr->getGlobalPos();
	iniLayer = getEntity()->getLayer();
	hoverScale = HOVER_SCALE;

	for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
	{
		// si es texto
		const auto texto = child->getEntity()->getComponent<TextComponent>();
		if (texto != nullptr)
		{
		}
	}

	resetTweensForward();
}

void Hover::update()
{
	if (!isOnHand) return;

	hoverTweenX.step(1);
	hoverTweenY.step(1);
	scaleTween.step(1);

	if (ih().mouseButtonDownEvent()) hasClicked = true;
	if (ih().mouseButtonUpEvent()) hasClicked = false;
	if (hasClicked)
	{
		intoHover = false;
		outoHover = false;
		tr->setGlobalScale(iniScale);
		resetEveryComponent();
		return;
	}

	const auto currTime = sdlutils().virtualTimer().currTime();
	if (mouseRaycast() == ent_)
	{
		// si el raton esta dentro de la carta
		if (!intoHover) // si no esta entrando en hover ya
			if (hoverTimer + hoverActivationSpeed <= currTime) // si ha pasado sufi tiempo
				onHoverEnter();
	}
	else
	{
		// si sale el raton de la carta
		hoverTimer = currTime; // se resetea el contador
		if (intoHover) // out of hover
			onHoverExit();
	}

	if (intoHover || outoHover)
	{
		updateEveryComponent();
	}
}

void Hover::onHoverEnter()
{
	iniScale = tr->getGlobalScale();
	intoHover = true;
	outoHover = false;
	//tr->setGlobalScale(hoverScale, hoverScale);
	resetTweensForward();
}

void Hover::onHoverExit()
{
	intoHover = false;
	outoHover = true;
	tr->setGlobalScale(iniScale);
	//resetEveryComponent();
	resetTweensBackward();
	updateEveryComponent();
}

void Hover::updateEveryComponent()
{
	if (checkTweenConstraints()) return;

	std::cout << hoverTweenX.peek() << std::endl;
	//std::cout << scaleTween.peek() << std::endl;

	// fondo de la carta
	spr->setOffset(
		hoverTweenX.peek(),
		hoverTweenY.peek()
	);
	//tr->setGlobalScale(scaleTween.peek(), scaleTween.peek());

	// textos
	for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
	{
		// si es texto
		const auto texto = child->getEntity()->getComponent<TextComponent>();
		if (texto != nullptr)
		{
			int x = 0, y = 0;
			if (texto->getText().at(0) == '+'
				|| texto->getText().at(0) == '-') // XXDDDDDDDDDDD
			{
				// es el texto del efecto
				x = EFFECT_OFFSET_X;
				y = EFFECT_OFFSET_Y;
			}
			else
			{
				// si no, son el coste y el valor
			}
			texto->setOffset(hoverTweenX.peek() + x, hoverTweenY.peek() + y);
			texto->setScale(Vector2D(hoverScale, hoverScale));
		}

		// si es imagen
		const auto imagen = child->getEntity()->getComponent<SpriteRenderer>();
		if (imagen != nullptr)
		{
			if (imagen->getTextID() == "card_sombra")
			{
				// si es la sombra
				imagen->setOffset(hoverTweenX.peek() - 2, hoverTweenY.peek() - 2);
			}
			else
			{
				// si no es la sombra, es la imagen de efecto
				imagen->setOffset(hoverTweenX.peek(), hoverTweenY.peek());
			}
		}
	}
}

void Hover::resetEveryComponent()
{
	// fondo de la carta
	spr->setOffset(
		0,
		0
	);

	// textos
	for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
	{
		// si es texto
		const auto texto = child->getEntity()->getComponent<TextComponent>();
		int x = 0, y = 0;
		if (texto != nullptr)
		{
			if (texto->getText().at(0) == '+'
				|| texto->getText().at(0) == '-') // XXDDDDDDDDDDD
			{
				// es el texto del efecto
				x = EFFECT_OFFSET_X;
				y = EFFECT_OFFSET_Y;
			}
			else
			{
			}
			texto->setOffset(x, y);
			texto->setScale(Vector2D(1, 1));
		}

		// si es imagen, puede tener texto
		const auto imagen = child->getEntity()->getComponent<SpriteRenderer>();
		if (imagen != nullptr)
		{
			if (imagen->getTextID() == "card_sombra")
			{
				// si es la sombra
				imagen->setOffset(-2, -2);
			}
			else
			{
				// si no, es la imagen de efecto
				imagen->setOffset(0, 0);
			}
		}
	}
}

bool Hover::checkTweenConstraints()
{
	bool outside = false;
	if ((hoverTweenX.peek() < -1000000) || (hoverTweenX.peek() > 1000000)) outside = true; // XDDXDDDX
	if ((hoverTweenY.peek() < -1000000) || (hoverTweenY.peek() > 1000000)) outside = true; // XDDXDDDX
	if ((scaleTween.peek() < -1000000) || (scaleTween.peek() > 1000000)) outside = true; // XDDXDDDX
	return outside;
}


void Hover::resetTweensForward()
{
	hoverTweenX =
		tweeny::from(0.f)
		.to(hoverOffset.getX())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(0.f)
		.to(hoverOffset.getY())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	scaleTween =
		tweeny::from(iniScale.getX())
		.to(hoverScale)
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);
}

void Hover::resetTweensBackward() /// *********
{
	// de vuelta de la posicion que sea a la inical
	hoverTweenX =
		tweeny::from(hoverTweenX.peek())
		.to(0.f)
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(hoverTweenY.peek())
		.to(0.f)
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	scaleTween =
		tweeny::from(scaleTween.peek())
		.to(iniScale.getX())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenX.seek(0);
	hoverTweenY.seek(0);
	scaleTween.seek(0);
}
