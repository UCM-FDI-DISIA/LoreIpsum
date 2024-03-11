#include "pch.h"
#include "KeyManager.h"
#include "Manager.h"
#include "SpriteRenderer.h"
#include "Transform.h"

#include <sstream>

KeyManager::KeyManager() : tr_(), pos_(), lastKey_(0), addToY_(100) {}

void 
KeyManager::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	pos_ = tr_->getGlobalPos() + Vector2D(10, 0); // El numero inicial vector posicion de la key hay que cambiarlo segun el tamaño de la imagen del libro

	imageIDs_.reserve(N);

	for (int i = 0; i < N; ++i) {
		std::stringstream p;
		p << "picto" << i + 1;
		imageIDs_.emplace_back(p.str());
	}
}

void
KeyManager::addKey(std::string s) {
	ecs::entity_t e = Instantiate(pos_);

	e->getComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
	e->addComponent<SpriteRenderer>(s);

	images_.emplace_back(e);
	pos_ = pos_ + Vector2D(0, addToY_);

	++lastKey_;
	if (lastKey_ == 3)
		pos_ = tr_->getGlobalPos() + Vector2D(110, 0);
}
