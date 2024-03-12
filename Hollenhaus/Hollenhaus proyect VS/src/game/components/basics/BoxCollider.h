#pragma once
#include "../ComponentUpdate.h"
#include "SpriteRenderer.h"
//#include "Transform.h"
#include "../../../utils/Vector2D.h"
#include "../../../utils/Collisions.h"

class Transform;
class SpriteRenderer;
class Vector2D;


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
	/// Para cambiar el tamano del collider
	/// </summary>
	/// <param name="newPosOffset"></param>
	void setSize(Vector2D newSize);
	Vector2D getSize() { return size_; }
	SDL_Rect* getRect() { return &collider_; }

	/// <summary>
	/// Settea si el tamano del collider depende del sprite, si tiene spriterenderer, por defecto est� en true
	/// </summary>
	/// <param name="_anchored"></param>
	void setAnchoredToSprite(bool _anchored) { anchoredToSprite_ = _anchored; }

	/// <summary>
	/// Devuelve true si el cursor esta sobre el collider
	/// </summary>
	/// <returns></returns>
	bool isCursorOver();

	void update() override;

private:

	// El tamano depende del sprite?
	bool anchoredToSprite_;

	// Puntero al transform
	Transform* transform_; 
	SpriteRenderer* spriteRenderer_;
	
	SDL_Rect collider_;
	//Collisions collider_;

	// Limites del collider
	Vector2D vertices[4];

	// Offset de la posicion
	Vector2D posOffset_;
	// Tamano del collider, depende de la escala del transform
	Vector2D size_;
};

