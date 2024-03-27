#include "pch.h"
#include "DialogueFactory_V0.h"
#include "../components/basics/TextComponent.h"
#include "../components/DialogueReader.h"
#include "../components/NextText.h"
#include "../components/TypeWriter.h"
#include "../components/AutoDialogue.h"
//#include "../components/DialogueEventCollection.h"
//#include "../components/DialogueDestroyer.h"

ecs::entity_t DialogueFactory_V0::createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size, 
	int speed, int cooldown, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint, 
	Text::TextAlignment textAlignment)
{
	ecs::entity_t dialogue = Instantiate();
	dialogue->addComponent<Transform>();
	//dialogue->addComponent<SpriteRenderer>(" ");
	dialogue->addComponent<BoxCollider>(pos, size);
	dialogue->addComponent<TextComponent>(" ", fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	dialogue->addComponent<TypeWriter>(speed);
	dialogue->addComponent<DialogueReader>(id, convo);
	dialogue->addComponent<NextText>();
	dialogue->addComponent<AutoDialogue>(cooldown);
	dialogue->setLayer(3);

	//dialogue->addComponent<DialogueEventCollection>();
	//dialogue->addComponent<DialogueDestroyer>();

	return dialogue;
}
