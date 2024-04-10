#pragma once
#include "../ComponentUpdate.h"


class NetGame
	:public ComponentUpdate
{
	NetGame();
	~NetGame();

	void initComponent() override;
	void update() override;
};

