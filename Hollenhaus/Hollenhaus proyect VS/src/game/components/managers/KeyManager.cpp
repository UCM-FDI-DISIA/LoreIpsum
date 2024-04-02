#include "pch.h"

#include "KeyManager.h"
#include "Manager.h"

#include "../basics/SpriteRenderer.h"
#include "../basics/Transform.h"
#include "../basics/TextComponent.h"

#include <sstream>

KeyManager::KeyManager() : addToY_(100), lastKey_(0), tr_(), pos_() {}

void 
KeyManager::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	pos_ = tr_->getGlobalPos() + Vector2D(10, 0); // El numero inicial vector posicion de la key hay que cambiarlo segun el tamaño de la imagen del libro
}

void
KeyManager::addKey(std::string s) {
	ecs::entity_t e = Instantiate(pos_); // Creamos la imagen

	e->getComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
	e->addComponent<SpriteRenderer>(s);

	// Creamos el texto
	ecs::entity_t txt = Instantiate(pos_ + Vector2D(e->getComponent<SpriteRenderer>()->getImageSize().getX(), 0));

	txt->addComponent<Transform>()->addParent(e->getComponent<Transform>());
	//txt->addComponent<TextComponent>(descs_[lastKey_]);

	keys_.emplace_back(e, txt);
	pos_ = pos_ + Vector2D(0, addToY_);

	++lastKey_;
	if (lastKey_ == 3)
		pos_ = tr_->getGlobalPos() + Vector2D(110, 0);
}
