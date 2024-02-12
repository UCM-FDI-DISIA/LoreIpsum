#pragma once

#include "Component.h"

class ComponentUpdate : public Component {

public:
	ComponentUpdate() :
		ent_()
	{}

	virtual ~ComponentUpdate() {};

	// Para pasarle un puntero a su entidad
	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	// Se invoca al añadir un componente a una entidad.
	// Para inicializar el componenete si es necesario.
	virtual void initCompomnent() {};

	// Para actualizar el estado
	virtual void update() {};

protected:
	Entity* ent_;
};

