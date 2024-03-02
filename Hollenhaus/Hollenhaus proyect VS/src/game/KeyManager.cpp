#include "KeyManager.h"
#include "Manager.h"
#include "SpriteRenderer.h"

#include <sstream>

KeyManager::KeyManager() {}

void 
KeyManager::initComponent() {
	imageIDs_.reserve(6);

	for (int i = 0; i < 6; ++i) {
		std::stringstream p;
		p << "picto" << i + 1;
		imageIDs_.emplace_back(p.str());
	}
}

void 
KeyManager::addKey(std::string s) {
	ecs::entity_t e = Instantiate();
	e->addComponent<SpriteRenderer>(s);
	e->addComponent<Transform>()->addParent(getEntity()->getComponent<Transform>());
	images_.emplace_back(e);
}




