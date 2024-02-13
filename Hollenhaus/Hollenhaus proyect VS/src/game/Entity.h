#pragma once

#include "ecs.h"
#include <array>
#include <vector>

class ComponentUpdate;
class ComponentRender;
class GameState;


/// <summary>
/// Clase entity vista en clase con algunas modificiaciones:
/// Usamos 2 listas de componentes, una de ComponentUpdate y otra de ComponentRender
/// Se gestionan las listas por separado
/// Necesitamos las 2 listas para tener un orden de renderizado y que los componentes no tengan
/// funciones vacias
/// </summary>

class Entity {


public:

	//Constructora, inicializamos todas las variables
	Entity(GameState* gs) :
		gameState(gs), cmpsU_(), currCmpsU_(), cmpsR_(), currCmpsR_(), alive_() {
		
		//reservamos la memoria para las listas de componentes
		currCmpsU_.reserve(ecs::maxComponentUId);
		currCmpsR_.reserve(ecs::maxComponentRId);
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

	//funciones publicas para consultar y cambiar el el estado de la entidad
	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }

	//consulta el gameState al que pertenece la entidad
	GameState* getGameState() { return gameState; }


private:

	bool alive_;
	GameState* gameState;

	//lista de componentes que tienen update
	std::vector<ComponentUpdate*> currCmpsU_;
	std::array<ComponentUpdate*, ecs::maxComponentUId> cmpsU_;

	//lista de componentes que tienen render
	std::vector<ComponentRender*> currCmpsR_;
	std::array<ComponentRender*, ecs::maxComponentRId> cmpsR_;

public:

	//añadir un componente a una entidad
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&&...args) {
		//creamos el componente
		T* c = new T(std::forward<Ts>(args)...);

		//guardamos el ID
		constexpr ecs::cmpId_t cId = T::id;

		//vemos si es un componente de tipo Update o no
		//Nota: consideramos que si no es de tipo Update es de tipo Render
		ComponentUpdate* p = dynamic_cast<ComponentUpdate*>(c);

		//si es de tipo update
		if (p != nullptr) {

			//nos aseguramos que no salimos del array
			static_assert(cId < ecs::maxComponentUId);
			//elimiamos este componente por si ya lo teniamos
			removeComponent<T>();
			//añadimos el componente a la lista y al array
			currCmpsU_.push_back(c);
			cmpsU_[cId] = c;

			//seteamos el contexto e inicializamos el componente
			c->setContext(this);
			c->initComponent();
		}
		else {//si es de tipo de render

			//nos aseguramos que no salimos del array
			static_assert(cId < ecs::maxComponentRId);

			//elimiamos este componente por si ya lo teniamos
			removeComponent<T>();
			//añadimos el componente a la lista y al array
			currCmpsR_.push_back(c);
			cmpsR_[cId] = c;

			//seteamos el contexto e inicializamos el componente
			c->setContext(this);
			c->initComponent();
		}

		return c;
	}

	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_t cId = T::id;
		if (cmpsU_[cId] != nullptr) {
			auto iter = std::find(currCmpsU_.begin(),
				currCmpsU_.end(),
				cmpsU_[cId]);
			currCmpsU_.erase(iter);
			delete cmpsU_[cId];
			cmpsU_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent() {
		constexpr cmpId_t cId = T::id;

		return static_cast<T*>(cmps_[cId]);
	}

	template<typename T>
	inline bool hasComponent() {
		constexpr cmpId_t cId = T::id;
		return cmpsU_[cId] != nullptr;
	}

	inline void update() {
		auto n = currCmpsU_.size();
		for (auto i = 0u; i < n; i++){}
			//currCmpsU_[i]->update();
	}

	inline void render() {
		auto n = currCmpsU_.size();
		for (auto i = 0u; i < n; i++){}
			//currCmpsU_[i]->render();
	}
};