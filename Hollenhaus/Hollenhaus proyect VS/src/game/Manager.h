#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include "Component.h"
#include "ecs.h"
#include "Entity.h"

namespace ecs {

class Manager {

	using entity_t = Entity*;
protected:
	std::vector<Entity*> ents_; //vector de entidades de cada estado

public:

	Manager();
	virtual ~Manager();

	Entity* addEntity(); //entidades en cada estado
	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //
	virtual void render();

	/*
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

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		// delete the current component, if any
		//
		removeComponent<T>(e);

		// create, initialise and install the new component
		//
		Component *c = new T(std::forward<Ts>(args)...);
		c->setContext(e, this);
		c->initComponent();
		e->cmps_[cId] = c;
		e->currCmps_.push_back(c);

		// return it to the user so i can be initialised if needed
		return static_cast<T*>(c);
	}

	// Removes the component T, from the entity.
	//
	template<typename T>
	inline void removeComponent(entity_t e) {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		if (e->cmps_[cId] != nullptr) {

			// find the element that is equal tocmps_[cId] (returns an iterator)
			//
			auto iter = std::find(e->currCmps_.begin(), e->currCmps_.end(),
					e->cmps_[cId]);

			// must have such a component
			assert(iter != e->currCmps_.end());

			// and then remove it
			e->currCmps_.erase(iter);

			// destroy it
			//
			delete e->cmps_[cId];

			// remove the pointer
			//
			e->cmps_[cId] = nullptr;
		}
	}

	// Returns the component, of the entity, that corresponds to position T,
	// casting it to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent(entity_t e) {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		return static_cast<T*>(e->cmps_[cId]);
	}

	// return true if there is a component with identifier T::id in the entity
	//
	template<typename T>
	inline bool hasComponent(entity_t e) {

		constexpr cmpId_t cId = T::id;
		assert(cId < ecs::maxComponentId);

		return e->cmps_[cId] != nullptr;
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
		auto n = e->currCmps_.size();
		for (auto i = 0u; i < n; i++)
			e->currCmps_[i]->update();
	}
	*/



private:
	std::array<entity_t, ecs::maxHandlerId> hdlrs_;
	std::array<std::vector<entity_t>, ecs::maxGroupId> entsByGroup_;
};


}