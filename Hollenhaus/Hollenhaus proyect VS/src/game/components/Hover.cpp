#include "..\pchs\pch.h"
#include "Hover.h"

void Hover::initComponent()
{
	tr = getEntity()->getComponent<Transform>();
	spr = getEntity()->getComponent<SpriteRenderer>();
}

void Hover::update()
{
	iniScale = tr->getGlobalScale();
	iniPos = tr->getGlobalPos();
	iniLayer = getEntity()->getLayer();
	getEntity()->getLastLayer()
}
