#pragma once
#include "ComponentUpdate.h"

class Transform;
class Vector2D;

class DragNoCombat : public ComponentUpdate
{
private:
	Transform* dragTransform; // transform de la carta draggeada

	Vector2D initialMousePos;
	Vector2D initialTransformPos;
	Vector2D initialTransformPosWithOffSet;

	void OnLeftClickDown();
	void OnLeftClickUp();

public:
	DragNoCombat();
	~DragNoCombat();

	void initComponent() override;
	void update() override;
};