#include "Entity.h"
#include "Manager.h"

namespace ecs {

	void Entity::setLayer(int nextLayer) {
		mngr().ChangeLayer(layer, nextLayer, this);
	}

}