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
	/// constructora vac�a, por defecto posOffset = (0,0) / size = (1,1)
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
	/// Para cambiar el tama�o del collider
	/// </summary>
	/// <param name="newPosOffset"></param>
	void setSize(Vector2D newSize);
	Vector2D getSize() { return size_; }
	SDL_Rect* getRect() { return &collider_; }

	/// <summary>
	/// Settea si el tama�o del collider depende del sprite, si tiene spriterenderer, por defecto est� en true
	/// </summary>
	/// <param name="_anchored"></param>
	void setAnchoredToSprite(bool _anchored) { anchoredToSprite_ = _anchored; }

	void update() override;

private:

	// El tamano depende del sprite?
	bool anchoredToSprite_;

	// Puntero al transform
	Transform* transform_; 
	SpriteRenderer* spriteRenderer_;
	
	SDL_Rect collider_;

	// Offset de la posicion
	Vector2D posOffset_;
	// Tamano del collider, depende de la escala del transform
	Vector2D size_;
};

