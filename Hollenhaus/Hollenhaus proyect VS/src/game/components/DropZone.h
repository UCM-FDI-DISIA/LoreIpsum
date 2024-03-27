#pragma once
#include "ComponentUpdate.h"
#include "./basics/BoxCollider.h"
#include "./managers/DrawerManager.h"
#include "./managers/PizarraManager.h"
#include "./Card.h"

class DropZone : public ComponentUpdate
{
private:
	Vector2D dropZonePos;
	BoxCollider* dropZoneCollider;

public:
	DropZone();
	~DropZone();

	void initComponent() override;
	void update() override;

	bool isOnDropZone(Transform* cardTransform);

	void moveToPizarra(DrawerManager* drawer, PizarraManager* pizarra, Card* card);
	void moveToDrawer(DrawerManager* drawer, PizarraManager* pizarra, Card* card);
};