#pragma once
#include "ComponentUpdate.h"

class BoxCollider;
class SendIPFromTextComponent;

class SendInvitationButton : public ComponentUpdate
{
public:
	SendInvitationButton();
	~SendInvitationButton() override;

	void initComponent() override;
	void update() override;

private:
	void clickButton();

	BoxCollider* bc;
	SendIPFromTextComponent* getIP;
};
