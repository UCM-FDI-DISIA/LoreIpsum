#pragma once
#include "GameState.h"

class Transform;

class JimboState :
	public GameState
{
public:
	JimboState();
	~JimboState() override;


	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;

private:
	ecs::entity_t legend_;
	ecs::entity_t e_;
	ecs::entity_t aa_;
};
