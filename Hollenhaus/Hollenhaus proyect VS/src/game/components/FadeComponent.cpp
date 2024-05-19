#include "..\pchs\pch.h"
#include "FadeComponent.h"

FadeComponent::FadeComponent()
{
}

FadeComponent::~FadeComponent()
{
}

void FadeComponent::initComponent()
{
	f = ent_->getComponent<SpriteRenderer>();
	t = ent_->getComponent<TextComponent>();

	if (f != nullptr) isImage = true;
	if (t != nullptr) isText = true;

	fadeIn = true;
	//Creamos el tween
	// FADE TWEEN
	fadetween =
		tweeny::from(0)
		.to(255)
		.during(15)
		.via(tweeny::easing::linear);
}

void FadeComponent::update()
{
	//Poner bool para que solo se haga al principio?
	if (fadeIn) {
		/*if (fadetween.progress() >= 1.0)
			fadeIn = false;*/

		fadetween.step(1); // avanza
		if (isImage)
			f->setOpacity(fadetween.peek());
		if (isText)
			t->setAlpha(fadetween.peek());
	}
	else {
		fadetween.backward();
		fadeIn = true;
	}
}

void FadeComponent::setFadeInFalse()
{
	fadeIn = false;
}


