#pragma once

#include <array>
#include <vector>

class Component;
class GameState;

class Entity {


public:

	Entity(GameState* gs) :
		gameState(gs), cmps_(), currCmps_(), alive_() {
		currCmps_.reserve(ecs::maxComponentId);
	}
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}
	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }
	GameState* getGameState() { return gameState; }


private:

	bool alive_;
	GameState* gameState;
	std::vector<Component*> currCmps_;
	std::array<Component*, ecs::maxComponentId> cmps_;


public:

	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& …args) {
		T* c = new T(std::forward<Ts>(args)…);

		constexpr cmpId_t cId = T::id;
		static_assert(cId < maxComponentId);

		removeComponent<T>();
		currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this);
		c->initComponent();
		return c;
	}

	inline void removeComponent(cmpId_t cId) {
		if (cmps_[cId] != nullptr) {
			auto iter = std::find(currCmps_.begin(),
				currCmps_.end(),
				cmps_[cId]);
			currCmps_.erase(iter);
			delete cmps_[cId];
			cmps_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent(cmpId_t cId) {
		return static_cast<T*>(cmps_[cId]);
	}

	inline bool hasComponent(cmpId_t cId) {
		return cmps_[cId] != nullptr;
	}

	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}

	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[I]->render();
	}
};