#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

class BoxCollider;
class SendIPFromTextComponent;

class SendInvitationButton : public ComponentUpdate
{
public:
	SendInvitationButton();
	~SendInvitationButton();

	void initComponent() override;
	void update() override;

private:
	void clickButton();

	BoxCollider* bc;
	SendIPFromTextComponent* getIP;
};

