#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

class TextComponent;
class NetLobby;

// M�todo que recoge una IP de un TextComponent y la env�a a NetLobby
class SendIPFromTextComponent : public ComponentUpdate
{
public:
	SendIPFromTextComponent(TextComponent* tc, NetLobby* nl);
	~SendIPFromTextComponent();

	void initComponent() override;
	void update() override;

	void sendIP();
private:
	TextComponent* tc;
	NetLobby* nl;
};

