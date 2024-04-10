#pragma once
#include "../ComponentUpdate.h"

#include <SDL_net.h>


class NetGame
	:public ComponentUpdate
{
public:

	NetGame();
	~NetGame();

	void initComponent() override;
	void update() override;




private:

	TCPsocket rival;

};

