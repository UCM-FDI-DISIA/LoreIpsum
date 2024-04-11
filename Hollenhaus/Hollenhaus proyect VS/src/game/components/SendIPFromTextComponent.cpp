#include "pch.h"
#include "SendIPFromTextComponent.h"
#include "basics/TextComponent.h"

SendIPFromTextComponent::SendIPFromTextComponent(TextComponent* textComponent)
{
	tc = textComponent;
}

SendIPFromTextComponent::~SendIPFromTextComponent()
{
}

void SendIPFromTextComponent::initComponent() 
{
}

void SendIPFromTextComponent::update()
{
}

void SendIPFromTextComponent::sendIP()
{
	TuVieja(tc->getText());
}
