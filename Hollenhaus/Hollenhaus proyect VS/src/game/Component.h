#pragma once

#include "ecs.h"

class Entity;

namespace ecs {


class Component
{
public:
	Component() :
		ent_()
	{}

	virtual ~Component() {};

	// Para pasarle un puntero a su entidad
	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	// Se invoca al anyadir un componente a una entidad.
	// Para inicializar el componenete si es necesario.
	virtual void initCompomnent() {};

protected:

	//puntero a la entidad a la que pertenece el componente
	Entity* ent_;


	constexpr static ecs::cmpId_t id = 0;
	// 2 opciones(segun sea un componentne de render o de update):
	//ecs::cmp::cmpUId::COMPONENT_ID
	//ecs::cmp::cmpRId::COMPONENT_ID
};

}
