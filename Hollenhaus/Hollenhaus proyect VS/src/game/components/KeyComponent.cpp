#include <../pchs/pch.h>

#include "KeyComponent.h"

#include "basics/TextComponent.h"

KeyComponent::KeyComponent(const int keys) :
	addToY_(100),
	NKeys_(keys),
	tr_(),
	sr_(),
	pos_(),
	firstOffset_(100, 150),
	secondOffset_(50, 150),
	bookWidth_(),
	font_(Fonts::GROTESK_16)
{
	// Inicializacion del vector con los nombres
	keyNames_.reserve(TOTAL_KEYS);

	keyNames_.emplace_back("esquina");
	keyNames_.emplace_back("centro");
	keyNames_.emplace_back("unblockable");
	keyNames_.emplace_back("flecha");
	keyNames_.emplace_back("superflecha");
	keyNames_.emplace_back("block");
}

void
KeyComponent::initComponent() {
	for (int i = 0; i < TOTAL_KEYS; ++i) {
		descs_.emplace_back(sdlutils().keys().at(keyNames_[i]).text()); // Descripciones desde el map
	}

	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	pos_ = tr_->getGlobalPos() + firstOffset_; // El numero inicial vector posicion de la key hay que cambiarlo segun el tamaño de la imagen del libro

	sr_ = ent_->getComponent<SpriteRenderer>();
	assert(sr_ != nullptr);

	bookWidth_ = sr_->getImageSize().getX();

	set();
}

void
KeyComponent::set() {
	for (int i = 0; i < NKeys_; ++i) {
		ecs::entity_t e = Instantiate(pos_); // Creamos la imagen

		e->getComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
		e->getComponent<Transform>()->setGlobalScale(0.15, 0.15);
		e->addComponent<SpriteRenderer>(keyNames_[i]);

		// Creamos el texto
		ecs::entity_t txt = Instantiate(pos_ + Vector2D(e->getComponent<SpriteRenderer>()->getImageSize().getX() * 0.5, 0));

		txt->getComponent<Transform>()->addParent(e->getComponent<Transform>());
		txt->addComponent<TextComponent>(descs_[i],
			font_,
			SDL_Color({ 0, 0, 0, 255 }),
			170,
			Text::BoxPivotPoint::LeftTop,
			Text::TextAlignment::Center);

		// Se añade el par al vector
		keys_.emplace_back(e, txt);
		pos_ = pos_ + Vector2D(0, addToY_); // Actualizamos la pos para la siguiente

		if (i + 1 == TOTAL_KEYS * 0.5)
			pos_ = Vector2D(tr_->getGlobalPos().getX() + bookWidth_ * 0.5, tr_->getGlobalPos().getY()) + secondOffset_;
	}
}
