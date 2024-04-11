#pragma once
#include "ComponentUpdate.h"

class TextComponent;
class NetLobby;

// Método que recoge una IP de un TextComponent y la envía a NetLobby
class SendIPFromTextComponent : public ComponentUpdate
{
public:
	SendIPFromTextComponent();
	~SendIPFromTextComponent();

	void initComponent() override;
	void update() override;

	void sendIP();
private:
	TextComponent* tc;
	NetLobby* nl;
};

