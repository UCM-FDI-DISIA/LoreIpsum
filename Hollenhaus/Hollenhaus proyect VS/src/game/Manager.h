#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <type_traits>
#include <map>
#include <list>

#include "Component.h"
#include "ecs.h"
#include "Entity.h"

//CUIDADO CON DEPENDENCIAS
#include "GameStateMachine.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

namespace ecs {

	using entity_t = Entity*;

class Manager {


protected:

	std::map<int, std::list<Entity*>> ordenRendering; //map de layers y lista de entidades

public:

	Manager();
	virtual ~Manager();

	virtual void Free();

	virtual void refresh(); //borra entidades no vivas
	
	//a�ade una entidad al mapa
	void AddEntityMap(int layer, Entity* e) {
		ordenRendering[layer].push_back(e);
	}
	
	void DeleteEntityMap(int layer, Entity* e) {
		auto it = ordenRendering[layer].begin();

		while (e != (*it)) {
			it++;
		}

		ordenRendering[layer].erase(it);
	}

	void ChangeLayer(int previousLayer, int nextLayer, Entity* e) {
		DeleteEntityMap(previousLayer, e);
		AddEntityMap(previousLayer, e);
	}

	// Adding an entity simply creates an instance of Entity, adds
	// it to the list of entities and returns it to the caller.
	//
	inline entity_t addEntity(ecs::grpId_t gId = ecs::grp::DEFAULT) {

		// create and initialise the entity
		auto e = new Entity(gId);
		e->alive_ = true;

		// add the entity 'e' to list of entities of the given group
		//
		// IMPORTANT NOTE:
		//
		// Currently we immediately add the entity to the list of entities,
		// so we will actually see them in this 'frame' if we traverse the list of
		// entities afterwards!
		//
		// A better solution would be to add them to an auxiliary list, and
		// define a method 'flush()' that moves them from the auxiliary list
		// to the corresponding list of entities.
		//
		// We will have to call 'flush()' in each iteration of the
		// main loop. This way we guarantee that entities that are added in one
		// 'frame' they will appear only in the next 'frame' -- I leave it as an
		// exercise for you ... it could be incorporated in 'refresh' as well.
		//
		entsByGroup_[gId].push_back(e);

		// return it to the caller
		//
		return e;
	}

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(entity_t e, bool alive) {
		e->alive_ = alive;
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive(entity_t e) {
		return e->alive_;
	}

	// Adds a component to an entity. It receives the type T (to be created),
	// and the list of arguments (if any) to be passed to the constructor.
	//
	template<typename T, typename ...Ts>
	inline T* addComponent(entity_t e, Ts &&... args) {	

		if (std::is_base_of<ComponentUpdate, T>::value) {

			// the component id
			cmpId_t cId = cmpUpdateId<T>;

			assert(cId < ecs::maxComponentUpdateId);

			// delete the current component, if any
			//
			removeComponent<T>(e);

			// create, initialise and install the new component
			//
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(e, this);

			ComponentUpdate* p = static_cast<ComponentUpdate*>(c);

			e->cmpsU_[cId] = p;
			e->currCmpsU_.push_back(p);

			c->initComponent();

			// return it to the user so i can be initialised if needed
			return static_cast<T*>(c);
		}
		else {

			// the component id
			cmpId_t cId = cmpRenderId<T>;

			assert(cId < ecs::maxComponentRenderId);

			// delete the current component, if any
			//
			removeComponent<T>(e);

			// create, initialise and install the new component
			//
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(e, this);

			ComponentRender* p = static_cast<ComponentRender*>(c);
			e->cmpsR_[cId] = p;
			e->currCmpsR_.push_back(p);


			c->initComponent();

			// return it to the user so i can be initialised if needed
			return static_cast<T*>(c);
		}
	

		
	}

	// Removes the component T, from the entity.
	//
	template<typename T>
	inline void removeComponent(entity_t e) {	

		if (std::is_base_of<ComponentUpdate, T>::value) {

			// the component id
			cmpId_t cId = cmpUpdateId<T>;

			assert(cId < ecs::maxComponentUpdateId);

			if (e->cmpsU_[cId] != nullptr) {

				// find the element that is equal tocmps_[cId] (returns an iterator)
				//
				auto iter = std::find(e->currCmpsU_.begin(), e->currCmpsU_.end(),
					e->cmpsU_[cId]);

				// must have such a component
				assert(iter != e->currCmpsU_.end());

				// and then remove it
				e->currCmpsU_.erase(iter);

				// destroy it
				//
				delete e->cmpsU_[cId];

				// remove the pointer
				//
				e->cmpsU_[cId] = nullptr;
			}
		}
		else {

			// the component id
			cmpId_t cId = cmpRenderId<T>;

			assert(cId < ecs::maxComponentRenderId);

			if (e->cmpsR_[cId] != nullptr) {

				// find the element that is equal tocmps_[cId] (returns an iterator)
				//
				auto iter = std::find(e->currCmpsR_.begin(), e->currCmpsR_.end(),
					e->cmpsR_[cId]);

				// must have such a component
				assert(iter != e->currCmpsR_.end());

				// and then remove it
				e->currCmpsR_.erase(iter);

				// destroy it
				//
				delete e->cmpsR_[cId];

				// remove the pointer
				//
				e->cmpsR_[cId] = nullptr;
			}
		}

		
	}

	// Returns the component, of the entity, that corresponds to position T,
	// casting it to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent(entity_t e) {

		if (std::is_base_of<ComponentUpdate, T>::value) {

			// the component id
			cmpId_t cId = cmpUpdateId<T>;

			assert(cId < ecs::maxComponentUpdateId);

			return dynamic_cast<T*>(e->cmpsU_[cId]);
		}
		else {

			// the component id
			cmpId_t cId = cmpRenderId<T>;

			assert(cId < ecs::maxComponentRenderId);

			return dynamic_cast<T*>(e->cmpsR_[cId]);
		}

	}

	// return true if there is a component with identifier T::id in the entity
	//
	template<typename T>
	inline bool hasComponent(entity_t e) {

		

		if (std::is_base_of<ComponentUpdate, T>::value) {

			cmpId_t cId = cmpUpdateId<T>;

			assert(cId < ecs::maxComponentUpdateId);

			return e->cmpsU_[cId] != nullptr;
		}
		else {

			cmpId_t cId = cmpRenderId<T>;

			assert(cId < ecs::maxComponentRenderId);

			return e->cmpsR_[cId] != nullptr;
		}	
	}

	// returns the entity's group 'gId'
	//
	inline ecs::grpId_t groupId(entity_t e) {
		return e->gId_;
	}

	// returns the vector of all entities
	//
	inline const auto& getEntities(grpId_t gId = ecs::grp::DEFAULT) {
		return entsByGroup_[gId];;
	}

	// associates the entity 'e' to the handler 'hId'
	//
	inline void setHandler(hdlrId_t hId, entity_t e) {
		assert(hId < ecs::maxHandlerId);
		hdlrs_[hId] = e;
	}

	// returns the entity associated to the handler 'hId'
	//
	inline entity_t getHandler(hdlrId_t hId) {
		assert(hId < ecs::maxHandlerId);
		return hdlrs_[hId];
	}

	// Updating  an entity simply calls the update of all
	// components
	//
	inline void update(entity_t e) {
		auto n = e->currCmpsU_.size();
		for (auto i = 0u; i < n; i++)
			e->currCmpsU_[i]->update();
	}
	// Rendering an entity simply calls the render of all
	// components
	//
	inline void render(entity_t e) {
		auto n = e->currCmpsR_.size();
		for (auto i = 0u; i < n; i++)
			e->currCmpsR_[i]->render();
	}

	// update all entities
	//
	void update() {
		for (auto& ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				update(ents[i]);
		}
	}

	// render all entities
	//
	void render() {
		for (auto& ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				render(ents[i]);
		}
	}



private:
	std::array<entity_t, ecs::maxHandlerId> hdlrs_;
	std::array<std::vector<entity_t>, ecs::maxGroupId> entsByGroup_;
};

#pragma region Entity templates


template<typename T,typename ...Ts>
T* Entity::addComponent(Ts &&... args) {
	return mngr().addComponent<T>(this, std::forward<Ts>(args)...);
}
template<typename T>
inline void Entity::removeComponent() {
	mngr().removeComponent<T>(this);
}
template<typename T>
inline T* Entity::getComponent() {
	return mngr().getComponent<T>();
}

template<typename T>
inline bool Entity::hasComponent() {
	return mngr().hasComponent<T>();
}

inline ecs::grpId_t Entity::groupId() {
	return mngr().groupId(this);
}

inline void Entity::setAlive(bool alive) {
	mngr().setAlive(this,alive);
}

inline bool Entity::isAlive() {
	return mngr().isAlive(this);
}

inline void Entity::setHandler(hdlrId_t hId) {
	mngr().setHandler(hId, this);
}


#pragma endregion



}


inline ecs::entity_t Instantiate(ecs::grpId_t gId = ecs::grp::DEFAULT) {
	return mngr().addEntity(gId);
}

inline ecs::entity_t Instantiate(Vector2D pos, ecs::grpId_t gId = ecs::grp::DEFAULT) {
	ecs::entity_t ent = Instantiate(gId);
	ent->addComponent<Transform>()->getGlobalPos().set(pos);
	return ent;
}