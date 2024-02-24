#include "Entity.h"
#include "Manager.h"

namespace ecs {

	Entity::Entity(grpId_t gId) :
		gId_(gId), cmpsU_(), currCmpsU_(), cmpsR_(), currCmpsR_(), alive_() {

		//reservamos la memoria para las listas de componentes
		currCmpsU_.reserve(ecs::maxComponentUpdateId);
		currCmpsR_.reserve(ecs::maxComponentRenderId);

		mngr().AddEntityMap(0, this);
	}

	void Entity::setLayer(int nextLayer) {
		mngr().ChangeLayer(layer, nextLayer, this);
	}

}