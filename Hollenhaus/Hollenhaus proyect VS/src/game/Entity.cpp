#include <../pchs/pch.h>

#include "Entity.h"
#include "components/managers/Manager.h"

namespace ecs {

	Entity::Entity(grpId_t gId) :
		gId_(gId), cmpsU_(), currCmpsU_(), cmpsR_(), currCmpsR_(), alive_() {

		//reservamos la memoria para las listas de componentes
		currCmpsU_.reserve(ecs::maxComponentUpdateId);
		currCmpsR_.reserve(ecs::maxComponentRenderId);


		//añadir a la layer
		mngr().AddEntityMap(0, this);
	}

	/// cambia la entidad a nextLayer y a sus hijos a nextLayer + n siendo n la generacion
	void Entity::setEveryLayer(int nextLayer) {
		changeLayer(nextLayer);
		if (getComponent<Transform>() != nullptr)
		{ 
			for (const auto child : getComponent<Transform>()->getChildren())
			{ // para cada hijo
				if (!child->getChildren().empty())
				{ // si el hijo tiene hijos
					child->getEntity()->setLayer(nextLayer + 1);
				} // si el hijo no es padre
				if (child->getEntity()->getLayer() > layer)
				{
					child->getEntity()->changeLayer(nextLayer + 1);
				}
			}
		}
	}

	void Entity::changeLayer(int nextLayer)
	{
		mngr().ChangeLayer(layer, nextLayer,this);
		layer = nextLayer;
	}

	/// devuelve la capa del ultimo de los hijos de una entidad, o de ella misma si no los tiene
	int Entity::getLastLayer()
	{
		int layer = getLayer();
		if (getComponent<Transform>() != nullptr)
		{
			for (const auto child : getComponent<Transform>()->getChildren())
			{
				if (!child->getChildren().empty())
				{ // si el hijo tiene hijos
					return child->getEntity()->getLastLayer();
				} // si el hijo no es padre
				if (child->getEntity()->getLayer() > layer)
				{
					layer = child->getEntity()->getLayer();
				}
			}
		}
		return layer;
	}
}
