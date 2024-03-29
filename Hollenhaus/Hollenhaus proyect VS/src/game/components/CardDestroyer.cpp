#include "pch.h"
#include "CardDestroyer.h"
#include "managers/Manager.h"

CardDestroyer::CardDestroyer()
{

}

CardDestroyer::~CardDestroyer()
{

}

void CardDestroyer::initComponent()
{
	obj = ent_;
}

void CardDestroyer::destroyCard()
{
	ent_->~Entity();
}
