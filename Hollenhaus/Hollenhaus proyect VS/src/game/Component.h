#pragma once

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
};

