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

SolCardComponent::SolCardComponent(int num, int t, bool b, int layer)
	:number(num), bocabajo(b), mainLayer(layer)
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

void SolCardComponent::setLayer(int newLayer)
{
	if (getEntity()->getComponent<Transform>() != nullptr)
	{
		for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
		{ 
			// para cada hijo
			if (child->getEntity()->getLayer() == (getEntity()->getLayer() - 1)) {
				child->getEntity()->changeLayer(newLayer - 1);
			}
			else {
				child->getEntity()->changeLayer(newLayer + 1);
			}
		}
	}
	getEntity()->changeLayer(newLayer);
}

