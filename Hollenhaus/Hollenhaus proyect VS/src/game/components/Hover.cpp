#include "..\pchs\pch.h"
#include "Hover.h"

void Hover::initComponent()
{
	tr = getEntity()->getComponent<Transform>();
	spr = getEntity()->getComponent<SpriteRenderer>();

	iniScale = tr->getGlobalScale();
	iniPos = tr->getGlobalPos();
	iniLayer = getEntity()->getLayer();
}

void Hover::update()
{

}

void Hover::onHoverEnter()
{
}

void Hover::onHoverExit()
{
}
