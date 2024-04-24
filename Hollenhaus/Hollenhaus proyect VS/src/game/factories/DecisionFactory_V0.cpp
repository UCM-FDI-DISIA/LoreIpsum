#include <../pchs/pch.h>

#include "DecisionFactory_V0.h"
#include "../components/basics/TextComponent.h"
#include "../components/ClickDecision.h"


void DecisionFactory_V0::createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer, int scene, int greenDecision, int redDecision)
{
	//tamanyo de los cuadros de texto
	Vector2D scaleBox = Vector2D(0.95, 0.7); //no tocar cerdos que se me descoloca

	// ----------ENTIDAD ACEPTAR COMBATE-----------
	ecs::entity_t accept = Instantiate();
	accept->addComponent<Transform>();
	accept->addComponent<SpriteRenderer>("greenRect");
	accept->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	accept->getComponent<Transform>()->addParent(parent->getComponent<Transform>());

	accept->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect

	accept->getComponent<Transform>()->setGlobalPos(pos);
	accept->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	accept->addComponent<TextComponent>("Si", fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	accept->setLayer(layer);

	accept->addComponent<ClickDecision>(greenDecision, parent, scene); //si decision es 0, se ira a scene PAIGRO AQUI

	// ----------ENTIDAD RECHAZAR COMBATE-----------
	ecs::entity_t deny = Instantiate();
	deny->addComponent<Transform>();
	deny->addComponent<SpriteRenderer>("redRect");
	deny->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	deny->getComponent<Transform>()->addParent(parent->getComponent<Transform>());

	//tamanyo de el cuadro de texto
	deny->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect

	//LUGAR
	Vector2D boxOffset = pos + Vector2D(130, 0);
	
	deny->getComponent<Transform>()->setGlobalPos(boxOffset);
	deny->getComponent<Transform>()->getGlobalPos().setX(100);
	deny->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	deny->addComponent<TextComponent>("Byebye", fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	deny->setLayer(layer);

	deny->addComponent<ClickDecision>(redDecision, parent, scene); //si decision es 1, no se ira a scene, pero se destruira dialogue

	//cuando aparezca el decision, el collider del parent (caja de dialogo) deberia anularse
	if (parent->hasComponent<BoxCollider>())
	{
		parent->removeComponent<BoxCollider>();
	}
}

void DecisionFactory_V0::setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp, Text::TextAlignment ta)
{
	fontID = fid;
	color = c;
	wrapLenght = wl;
	boxPivotPoint = bpp;
	textAlignment = ta;
}
