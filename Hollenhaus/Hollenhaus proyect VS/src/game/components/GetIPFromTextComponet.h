#pragma once
#include "ComponentUpdate.h"

class TextComponent;
class NetLobby;

// M�todo que recoge una IP de un TextComponent y la env�a a NetLobby
class GetIPFromTextComponet : public ComponentUpdate
{
public:
	GetIPFromTextComponet();
	~GetIPFromTextComponet();

	void initComponent() override;
	void update() override;

	void sendIP();
private:
	TextComponent* tc;
	NetLobby* nl;
};

