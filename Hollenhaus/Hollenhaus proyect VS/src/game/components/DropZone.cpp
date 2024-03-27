#include "pch.h"
#include "DropZone.h"
#include "managers/Manager.h"
#include "../Entity.h"

DropZone::DropZone() { }

DropZone::~DropZone() { }

void DropZone::initComponent() { }

void DropZone::update() { }

bool DropZone::isOnDropZone(Transform* cardTransform)
{
	// devuelve true si el lt y el rb de la carta estan en el dropZone
	return (dropZoneCollider->PointOver(cardTransform->getGlobalPos()) &&					// lt
		dropZoneCollider->PointOver(cardTransform->getGlobalPos() +							// rb ->
			(cardTransform->getEntity()->getComponent<SpriteRenderer>()->getImageSize() *	// el lt + el tamanio del sprite
				cardTransform->getGlobalScale().getX())));									// con la escala aplicada
}