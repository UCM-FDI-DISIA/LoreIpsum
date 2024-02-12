#pragma once

#include "Component.h"

class ComponentRender : public Component {

public:
	ComponentRender() :
		ent_()
	{}

	virtual ~ComponentRender() {};

	// Para pasarle un puntero a su entidad
	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	// Se invoca al añadir un componente a una entidad.
	// Para inicializar el componenete si es necesario.
	virtual void initCompomnent() {};

	// Para renderizar el estado
	virtual void render() const {};

protected:
	Entity* ent_;
};