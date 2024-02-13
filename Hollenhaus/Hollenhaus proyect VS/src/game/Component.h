#pragma once

#include "ecs.h"

class Entity;

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

	// Se invoca al añadir un componente a una entidad.
	// Para inicializar el componenete si es necesario.
	virtual void initCompomnent() {};

protected:
	Entity* ent_;


	constexpr static ecs::cmpId_t id = 0;
	// 2 opciones(segun sea un componentne de render o de update):
	//ecs::cmp::cmpUId::COMPONENT_ID
	//ecs::cmp::cmpRId::COMPONENT_ID
};

