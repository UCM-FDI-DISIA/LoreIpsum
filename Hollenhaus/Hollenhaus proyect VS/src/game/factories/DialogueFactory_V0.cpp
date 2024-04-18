#include "pch.h"
#include "DialogueFactory_V0.h"
#include "../components/basics/TextComponent.h"
#include "../components/DialogueReader.h"
#include "../components/NextText.h"
#include "../components/TypeWriter.h"
#include "../components/AutoDialogue.h"
//#include "../components/DialogueEventCollection.h"
#include "../components/DialogueDestroyer.h"


// De Luis: Esto habría que refactorizarlo en algún momento.
// El tamanio del diálogo depende del tamanio de la textura "whiteRect", motivo por el cual no funciona el parámetro size.
// Además, el transform del dialogue es escalado, lo cual no es buena idea ya que afecta a los tamanios de otros elementos.
// He metido el texto en una entidad hija del dialogue, pero el componente transform no trabaja correctamente con los hijos, 
// asi que hay que hacer apanios un poco feos
// El margen entre el texto y la caja de diálogo tambien es un numero mágico
// En general hay qe refactorizar para que crear diálogos sea una tarea sencilla y parametrizable.

ecs::entity_t DialogueFactory_V0::createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size, 
	int speed, int cooldown, ecs::entity_t parent, int layer, bool auto_)
{
	ecs::entity_t dialogue = Instantiate();


	dialogue->addComponent<Transform>();
	dialogue->addComponent<SpriteRenderer>("whiteRect");
	dialogue->addComponent<BoxCollider>(); //pos -> se le suma la posicion de la entidad
	dialogue->getComponent<Transform>()->addParent(parent->getComponent<Transform>());
	
	//tamanyo de el cuadro de texto
	Vector2D scaleBox = Vector2D(2,2);	
	//dialogue->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect
	dialogue->getComponent<Transform>()->getRelativeScale().set(size.getX(), size.getY()); //escala del whiteRect

	dialogue->getComponent<Transform>()->setGlobalPos(pos);
	dialogue->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	// el texto se encuentra en una entidad hija
	Vector2D margin = Vector2D(10, 10);
	ecs::entity_t text = Instantiate();
	auto textTR = text->addComponent<Transform>();
	textTR->addParent(dialogue->getComponent<Transform>());
	//text->addComponent<BoxCollider>()->setSize(dialogue->getComponent<SpriteRenderer>()->getImageSize() - margin * 8);
	Vector2D localPos = dialogue->getComponent<Transform>()->getGlobalPos();
	localPos = localPos + margin;
	textTR->setGlobalPos(localPos);
	text->addComponent<DialogueDestroyer>(parent);
	text->addComponent<TextComponent>(" ", fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	text->addComponent<TypeWriter>(speed);
	text->addComponent<DialogueReader>(id, convo);
	text->addComponent<NextText>();

	text->getComponent<NextText>()->setCollider(dialogue->getComponent<BoxCollider>());

	if (auto_) {
		text->addComponent<AutoDialogue>(cooldown);
	}
	else {
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
