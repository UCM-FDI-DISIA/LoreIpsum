#include <../pchs/pch.h>

#include "DialogueFactory_V0.h"
#include "../components/basics/TextComponent.h"
#include "../components/DialogueReader.h"
#include "../components/NextText.h"
#include "../components/TypeWriter.h"
#include "../components/AutoDialogue.h"
//#include "../components/DialogueEventCollection.h"
#include "../components/DialogueDestroyer.h"
#include "../components/DialogueBoxDestroyer.h"

#include "../components/FadeComponent.h"


// Ahora si

ecs::entity_t DialogueFactory_V0::createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
                                                 int speed, int cooldown, ecs::entity_t parent, int layer, bool auto_)
{
	Transform* parentTr = parent->getComponent<Transform>();
	ecs::entity_t dialogue = Instantiate();

	TuVieja("Empieza dialogo");

	Transform* tr = dialogue->addComponent<Transform>();
	SpriteRenderer* sr = dialogue->addComponent<SpriteRenderer>("whiteRect");
	sr->setOpacity(0);
	dialogue->addComponent<FadeComponent>();
	dialogue->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	tr->addParent(parentTr);

	tr->setGlobalScale((0.25f / parentTr->getGlobalScale().getX()) * size.getX(),
	                   (0.25f / parentTr->getGlobalScale().getY()) * size.getY()); //escala del whiteRect
	tr->setGlobalPos(pos);
	dialogue->getComponent<BoxCollider>()->setAnchoredToSprite(true);


	// el texto se encuentra en una entidad hija

	ecs::entity_t text = Instantiate();
	auto textTR = text->addComponent<Transform>();
	textTR->addParent(dialogue->getComponent<Transform>());
	Vector2D localPos = dialogue->getComponent<Transform>()->getGlobalPos();

	text->addComponent<DialogueDestroyer>(parent);
	TextComponent* tc = text->addComponent<TextComponent>(
		" ", fontID, color, wrapLenght, 
		boxPivotPoint, Text::Center);

	// Podria hacer llorar a un matematico con esto pero funciona
	auto dialogueWidth = sr->getTexture()->width() * tr->getGlobalScale().getX();
	auto textWidth = tc->getTexture()->width() * tr->getGlobalScale().getX();
	auto diff = dialogueWidth - textWidth;
	auto marginX = diff / 2;

	auto margin = Vector2D(marginX * tr->getGlobalScale().getX() - 10, 50 * tr->getGlobalScale().getY());
	localPos = localPos + margin;
	textTR->setGlobalPos(localPos);

	text->addComponent<TypeWriter>(speed);
	text->addComponent<DialogueReader>(id, convo);
	text->addComponent<NextText>();
	text->addComponent<FadeComponent>();

	text->getComponent<NextText>()->setCollider(dialogue->getComponent<BoxCollider>());

	// Componente dialogueboxdestroyer que tiene metodo destroy que llama al metodo del dialogue desroyer del hijo
	dialogue->addComponent<DialogueBoxDestroyer>(text);

	if (auto_)
	{
		text->addComponent<AutoDialogue>(cooldown);
	}
	else
	{
		// quitar el collider¿¿?¿?¿
	}


	dialogue->setLayer(layer);
	text->setLayer(layer + 1);

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
