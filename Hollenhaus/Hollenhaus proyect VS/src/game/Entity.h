#pragma once

#include "ecs.h"
#include <array>
#include <vector>

//class ComponentUpdate;
//class ComponentRender;

//CUIDADO: PODRIA HABER DEPENDENCIAS CIRCULARES, si ocurre, mover update y render a cpp
#include "ComponentUpdate.h"
#include "ComponentRender.h"


/// <summary>
/// Clase entity vista en clase con algunas modificiaciones:
/// Usamos 2 listas de componentes, una de ComponentUpdate y otra de ComponentRender
/// Se gestionan las listas por separado
/// Necesitamos las 2 listas para tener un orden de renderizado y que los componentes no tengan
/// funciones vacias
/// </summary>


namespace ecs {

class Manager;

class Entity {


public:

	//Constructora, inicializamos todas las variables
	Entity(grpId_t gId) :
		gId_(gId), cmpsU_(), currCmpsU_(), cmpsR_(), currCmpsR_(), alive_() {
		
		//reservamos la memoria para las listas de componentes
		currCmpsU_.reserve(ecs::maxComponentUpdateId);
		currCmpsR_.reserve(ecs::maxComponentRenderId);
	}

	//eliminamos los componentes de las 2 listas
	virtual ~Entity() {
		for (auto c : currCmpsU_) {
			delete c;
		}
		for (auto c : currCmpsR_) {
			delete c;
		}
	}

private:

	bool alive_;
	grpId_t gId_;

	//lista de componentes que tienen update
	std::vector<ComponentUpdate*> currCmpsU_;
	std::array<ComponentUpdate*, ecs::maxComponentUpdateId> cmpsU_;

	//lista de componentes que tienen render
	std::vector<ComponentRender*> currCmpsR_;
	std::array<ComponentRender*, ecs::maxComponentRenderId> cmpsR_;

	//layer para el orden de renderizado
	int layer = 0;

public:

	friend Manager;
};

}
