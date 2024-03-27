#pragma once
#include "ComponentUpdate.h"

class DropZone : public ComponentUpdate
{
private:
	Vector2D dropZonePos;

public:
	DropZone();
	~DropZone();

	void initComponent() override;
	void update() override;
};