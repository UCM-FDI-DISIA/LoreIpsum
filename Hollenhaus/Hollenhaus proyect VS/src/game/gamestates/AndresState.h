#pragma once
#include "GameState.h"

class AndresState :
	public GameState
{
public:
	AndresState();
	~AndresState() override;


	void refresh() override;
	void update() override;
	void render() const override;

private:
	ecs::entity_t hand_;
};
