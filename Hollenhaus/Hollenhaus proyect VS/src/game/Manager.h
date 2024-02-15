#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <type_traits>

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

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //
	virtual void render();

	
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


		if (std::is_base_of<ComponentUpdate, T>::value) {
			static_assert(cId < ecs::maxComponentUId);

			// delete the current component, if any
			//
			removeComponent<T>(e);

			// create, initialise and install the new component
			//
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(e, this);
			c->initComponent();

			e->cmpsU_[cId] = c;
			e->currCmpsU_.push_back(c);

			// return it to the user so i can be initialised if needed
			return static_cast<T*>(c);
		}
		else {
			static_assert(cId < ecs::maxComponentRId);

			// delete the current component, if any
			//
			removeComponent<T>(e);

			// create, initialise and install the new component
			//
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(e, this);
			c->initComponent();

			e->cmpsR_[cId] = c;
			e->currCmpsR_.push_back(c);

			// return it to the user so i can be initialised if needed
			return static_cast<T*>(c);
		}
	

		
	}

	// Removes the component T, from the entity.
	//
	template<typename T>
	inline void removeComponent(entity_t e) {

		// the component id
		constexpr cmpId_t cId = ecs::cmpId<T>;

		if (std::is_base_of<ComponentUpdate, T>::value) {
			static_assert(cId < ecs::maxComponentUId);

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
			static_assert(cId < ecs::maxComponentRId);

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

		// the component id
		constexpr cmpId_t cId = cmpId<T>;

		if (std::is_base_of<ComponentUpdate, T>::value) {
			static_assert(cId < ecs::maxComponentUId);
			return static_cast<T*>(e->cmpsU_[cId]);
		}
		else {
			static_assert(cId < ecs::maxComponentRId);
			return static_cast<T*>(e->cmpsR_[cId]);
		}

	}

	// return true if there is a component with identifier T::id in the entity
	//
	template<typename T>
	inline bool hasComponent(entity_t e) {

		constexpr cmpId_t cId = T::id;

		if (std::is_base_of<ComponentUpdate, T>::value) {
			assert(cId < ecs::maxComponentUId);

			return e->cmpsU_[cId] != nullptr;
		}
		else {
			assert(cId < ecs::maxComponentRId);

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


}