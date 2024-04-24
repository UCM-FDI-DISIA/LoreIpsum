#include <../pchs/pch.h>

#include "Entity.h"
#include "components/managers/Manager.h"

namespace ecs
{
	Entity::Entity(grpId_t gId) :
		alive_(), gId_(gId), currCmpsU_(), cmpsU_(), currCmpsR_(), cmpsR_()
	{
		//reservamos la memoria para las listas de componentes
		currCmpsU_.reserve(maxComponentUpdateId);
		currCmpsR_.reserve(maxComponentRenderId);


		//añadir a la layer
		mngr().AddEntityMap(0, this);
	}

	void Entity::setLayer(int nextLayer)
	{
		mngr().ChangeLayer(layer, nextLayer, this);
		layer = nextLayer;
	}
}
