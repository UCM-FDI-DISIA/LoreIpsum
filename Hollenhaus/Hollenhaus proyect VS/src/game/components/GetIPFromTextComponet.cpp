#include "pch.h"
#include "GetIPFromTextComponet.h"
#include "basics/TextComponent.h"

GetIPFromTextComponet::GetIPFromTextComponet()
{
}

GetIPFromTextComponet::~GetIPFromTextComponet()
{
}

void GetIPFromTextComponet::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
}

void GetIPFromTextComponet::update()
{
}

void GetIPFromTextComponet::sendIP()
{
	tc->getText();
}
