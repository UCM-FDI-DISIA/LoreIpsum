#include "KeyManager.h"
#include "Manager.h"

KeyManager::KeyManager() {}

void 
KeyManager::initComponent() {
	imageIDs_.emplace_back("picto1");

	for (int i = 0; i < imageIDs_.size(); ++i) {
		ecs::entity_t e = Instantiate();
		images_.emplace_back(e);
		images_[i]->addComponent<SpriteRenderer>("picto1");
	}
}




