#pragma once
#include "game/ComponentUpdate.h"
#include "SDL.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "utils/Vector2D.h"

class BoxCollider :public ComponentUpdate
{
public:
	BoxCollider();

	void initComponent() override;

	void update() override;

private:
	Transform* transform_;
	SpriteRenderer* spriteRenderer_;
	SDL_Rect collider_;
	Vector2D offset_;
};

