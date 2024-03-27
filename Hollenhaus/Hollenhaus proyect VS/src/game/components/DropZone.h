#pragma once
#include "ComponentUpdate.h"
#include "./basics/BoxCollider.h"

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
};