#include <../pchs/pch.h>

#include "SolCardComponent.h"
#include "../../utils/Vector2D.h"
#include "../components/basics/TextComponent.h"
#include "DecisionComponent.h"

//------Factorias.
#include "../factories/Factory.h"

SolCardComponent::SolCardComponent()
{

}

SolCardComponent::SolCardComponent(int num, int t, bool b)
	:number(num), bocabajo(b)
{ 
	myType = (tipo)t;
}

SolCardComponent::~SolCardComponent()
{
	
}

void SolCardComponent::initComponent()
{
	
}

void SolCardComponent::update()
{
	
}

