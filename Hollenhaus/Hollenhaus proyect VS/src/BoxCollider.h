#pragma once
#include "game/ComponentUpdate.h"
#include "SDL.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "utils/Vector2D.h"

class BoxCollider :public ComponentUpdate
{
public:
	/// <summary>
	/// constructora vacía, por defecto posOffset = (0,0) / size = (1,1)
	/// </summary>
	BoxCollider();
	/// <param name="posOffset"> Por defecto esta a 0</param>
	/// <param name="size"> Por defecto esta a 1</param>
	BoxCollider(Vector2D posOffset, Vector2D size);

	void initComponent() override;

	/// <summary>
	/// Para cambiar el offset de la posicion del collider
	/// </summary>
	/// <param name="newPosOffset"></param>
	void setPosOffset(Vector2D newPosOffset);
	Vector2D getPosOffset() { return posOffset_; }

	/// <summary>
	/// Para cambiar el tamaño del collider
	/// </summary>
	/// <param name="newPosOffset"></param>
	void setSize(Vector2D newSize);
	Vector2D getSize() { return size_; }
	SDL_Rect* getRect() { return &collider_; }

	void update() override;

private:
	Transform* transform_;
	SpriteRenderer* spriteRenderer_;
	SDL_Rect collider_;
	Vector2D posOffset_;
	Vector2D size_;
};

