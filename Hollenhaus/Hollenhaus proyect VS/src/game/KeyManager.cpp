#include "KeyManager.h"
#include "Manager.h"
#include "SpriteRenderer.h"
#include "Transform.h"

#include <sstream>

KeyManager::KeyManager() {}

void 
KeyManager::initComponent() {
	imageIDs_.reserve(N);

	for (int i = 0; i < N; ++i) {
		std::stringstream p;
		p << "picto" << i + 1;
		imageIDs_.emplace_back(p.str());
	}
}

void
KeyManager::addKey(std::string s) {
	ecs::entity_t e = Instantiate();
	e->addComponent<Transform>();
	e->getComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
	e->addComponent<SpriteRenderer>(s);
	images_.emplace_back(e);
}
