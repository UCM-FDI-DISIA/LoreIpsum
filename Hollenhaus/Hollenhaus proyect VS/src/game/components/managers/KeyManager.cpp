#include "pch.h"

#include "KeyManager.h"
#include "Manager.h"

#include "../basics/SpriteRenderer.h"
#include "../basics/Transform.h"
#include "../basics/TextComponent.h"

KeyManager::KeyManager() : 
	addToY_(100), 
	lastKey_(0), 
	tr_(), 
	pos_(), 
	font_("8bit_size_20") 
{
	keyNames_.reserve(NUMBER_OF_KEYS);

	keyNames_.emplace_back("esquina");
	keyNames_.emplace_back("centro");
	keyNames_.emplace_back("unblockable");
	keyNames_.emplace_back("flecha");
	keyNames_.emplace_back("superflecha");
	keyNames_.emplace_back("block");
}

void 
KeyManager::initComponent() {
	for (int i = 0; i < NUMBER_OF_KEYS; ++i) {
		descs_.emplace_back(sdlutils().keys().at(keyNames_[i]).text());
	}

	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	pos_ = tr_->getGlobalPos() + Vector2D(10, 0); // El numero inicial vector posicion de la key hay que cambiarlo segun el tamaño de la imagen del libro
}

void
KeyManager::addKey() {
	ecs::entity_t e = Instantiate(pos_); // Creamos la imagen

	e->getComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
	e->addComponent<SpriteRenderer>(keyNames_[lastKey_]);

	// Creamos el texto
	ecs::entity_t txt = Instantiate(pos_ + Vector2D(e->getComponent<SpriteRenderer>()->getImageSize().getX(), 0));

	txt->addComponent<Transform>()->addParent(e->getComponent<Transform>());
	txt->addComponent<TextComponent>(descs_[lastKey_], 
									font_, 
									SDL_Color({ 0, 0, 0, 255 }), 
									150,
									Text::BoxPivotPoint::LeftTop, 
									Text::TextAlignment::Center);

	keys_.emplace_back(e, txt);
	pos_ = pos_ + Vector2D(0, addToY_);

	++lastKey_;
	if (lastKey_ == 3)
		pos_ = tr_->getGlobalPos() + Vector2D(110, 0);
}

/*{
  "id": "flecha",
  "text": "Su efecto se aplica a la carta adyacente en la dirección a la que apunta"
},
{
  "id": "superflecha",
  "text": "Su efecto se aplica todas las cartas en la dirección a la que apunta"
},
{
  "id": "block",
  "text": "Anula la habilidad de la carta adyacente en la dirección en la que apunta"
}*/
