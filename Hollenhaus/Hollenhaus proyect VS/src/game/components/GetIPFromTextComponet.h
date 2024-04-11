#pragma once
#include "ComponentUpdate.h"

class TextComponent;
class NetLobby;

// Método que recoge una IP de un TextComponent y la envía a NetLobby
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

