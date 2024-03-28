#include "pch.h"
#include "DialogueFactory_V0.h"
#include "../components/basics/TextComponent.h"
#include "../components/DialogueReader.h"
#include "../components/NextText.h"
#include "../components/TypeWriter.h"
#include "../components/AutoDialogue.h"
//#include "../components/DialogueEventCollection.h"
#include "../components/DialogueDestroyer.h"

ecs::entity_t DialogueFactory_V0::createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size, 
	int speed, int cooldown, ecs::entity_t parent, int layer)
{
	ecs::entity_t dialogue = Instantiate();

	Vector2D sizebox = Vector2D(0.5, 0.5);
	dialogue->addComponent<Transform>();
	dialogue->addComponent<SpriteRenderer>("whiteRect");
	dialogue->addComponent<BoxCollider>(pos, size); //pos -> se le suma la posicion de la entidad
	dialogue->getComponent<Transform>()->addParent(parent->getComponent<Transform>());
	
	//dialogue->addComponent<SpriteRenderer>(" ");
	dialogue->addComponent<DialogueDestroyer>();
	dialogue->addComponent<TextComponent>(" ", fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	dialogue->getComponent<Transform>()->getRelativeScale().set(sizebox.getX(), sizebox.getY());
	dialogue->getComponent<Transform>()->setGlobalPos(pos);
	//dialogue->getComponent<Transform>()->setGlobalScale(size);
	dialogue->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	dialogue->addComponent<TypeWriter>(speed);
	dialogue->addComponent<DialogueReader>(id, convo);
	dialogue->addComponent<NextText>();
	dialogue->addComponent<AutoDialogue>(cooldown);
	dialogue->setLayer(layer);

	//dialogue->addComponent<DialogueEventCollection>();
	

	return dialogue;
}

void DialogueFactory_V0::setTextValues(std::string fid, SDL_Color c, Uint32 wl, Text::BoxPivotPoint bpp,
	Text::TextAlignment ta)
{
	fontID = fid;
	color = c;
	wrapLenght = wl;
	boxPivotPoint = bpp;
	textAlignment = ta;

}
