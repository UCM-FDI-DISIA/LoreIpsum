#pragma once

#include "ecs.h"
#include <array>
#include <vector>

class ComponentUpdate;
class ComponentRender;
class GameState;

class Entity {


public:

	Entity(GameState* gs) :
		gameState(gs), cmpsU_(), currCmpsU_(), alive_() {
		currCmpsU_.reserve(ecs::maxComponentUId);
	}
	virtual ~Entity() {
		for (auto c : currCmpsU_) {
			delete c;
		}
	}

	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }
	GameState* getGameState() { return gameState; }


private:

	bool alive_;
	GameState* gameState;
	std::vector<ComponentUpdate*> currCmpsU_;
	std::array<ComponentUpdate*, ecs::maxComponentUId> cmpsU_;

	std::vector<ComponentRender*> currCmpsR_;
	std::array<ComponentRender*, ecs::maxComponentRId> cmpsR_;

public:

	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&&...args) {
		T* c = new T(std::forward<Ts>(args)...);

		constexpr cmpId_t cId = T::id;
		static_assert(cId < maxComponentId);

		removeComponent<T>();
		currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this);
		c->initComponent();
		return c;
	}

	inline void removeComponent(ecs::cmpId_t cId) {
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
	inline T* getComponent(ecs::cmpId_t cId) {
		return static_cast<T*>(cmps_[cId]);
	}

	inline bool hasComponent(ecs::cmpId_t cId) {
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