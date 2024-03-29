#include "pch.h"
#include "DecisionFactory_V0.h"


void DecisionFactory_V0::createPopUp(Vector2D pos, Vector2D size, ecs::entity_t parent)
{
	// ----------ENTIDAD ACEPTAR COMBATE-----------
	ecs::entity_t accept = Instantiate();
	accept->addComponent<Transform>();
	accept->addComponent<SpriteRenderer>("greenRect");
	accept->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	accept->getComponent<Transform>()->addParent(parent->getComponent<Transform>());

	//tamanyo de el cuadro de texto
	Vector2D scaleBox = Vector2D(2, 2);
	accept->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect

	accept->getComponent<Transform>()->setGlobalPos(pos);
	accept->getComponent<BoxCollider>()->setAnchoredToSprite(true);



	// ----------ENTIDAD RECHAZAR COMBATE-----------
	ecs::entity_t deny = Instantiate();
	deny->addComponent<Transform>();
	deny->addComponent<SpriteRenderer>("redRect");
	deny->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	deny->getComponent<Transform>()->addParent(parent->getComponent<Transform>());

	//tamanyo de el cuadro de texto
	Vector2D scaleBox = Vector2D(2, 2);
	deny->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect

	deny->getComponent<Transform>()->setGlobalPos(pos);
	deny->getComponent<BoxCollider>()->setAnchoredToSprite(true);

}

void DecisionFactory_V0::setTextValues(std::string fid, SDL_Color c, Text::BoxPivotPoint bpp, Text::TextAlignment ta)
{
	fontID = fid;
	color = c;
	boxPivotPoint = bpp;
	textAlignment = ta;
}
