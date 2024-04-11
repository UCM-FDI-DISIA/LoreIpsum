#include "pch.h"
#include "SendIPFromTextComponent.h"
#include "basics/TextComponent.h"

SendIPFromTextComponent::SendIPFromTextComponent()
{
}

SendIPFromTextComponent::~SendIPFromTextComponent()
{
}

void SendIPFromTextComponent::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
}

void SendIPFromTextComponent::update()
{
}

void SendIPFromTextComponent::sendIP()
{
	TuVieja(tc->getText());
}
