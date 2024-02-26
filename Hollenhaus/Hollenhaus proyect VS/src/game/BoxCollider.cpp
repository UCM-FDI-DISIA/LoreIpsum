#pragma once
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "Manager.h"
#include "Transform.h"
#include "ColliderRender.h"
#include "../sdlutils/InputHandler.h"

BoxCollider::BoxCollider() :BoxCollider(Vector2D(0, 0), Vector2D(1, 1))
{}

BoxCollider::BoxCollider(Vector2D posOffset, Vector2D size) :
	transform_(),
	spriteRenderer_(),
	collider_(),
	posOffset_(posOffset),
	size_(size)
{
	
}

void BoxCollider::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);



	spriteRenderer_ = mngr_->getComponent<SpriteRenderer>(ent_);

	anchoredToSprite_ = spriteRenderer_ != nullptr;

	if (anchoredToSprite_) {
		size_.set(spriteRenderer_->getTexture()->width(), spriteRenderer_->getTexture()->height());
	}
	else {
		size_.set(100, 100);
	}


	collider_.w = size_.getX();
	collider_.h = size_.getY();
	/*
	if (spriteRenderer_ != nullptr) {
		size_.set(spriteRenderer_->getTexture()->width(), spriteRenderer_->getTexture()->height());
		anchoredToSprite_ = true;
	}
	else
	{
		anchoredToSprite_ = false;
	}*/

#ifdef _DEBUG
	mngr_->addComponent<ColliderRender>(ent_);
#endif // DEBUG

}

void BoxCollider::update() {
	collider_.x = transform_->getGlobalPos().getX() + posOffset_.getX();
	collider_.y = transform_->getGlobalPos().getY() + posOffset_.getY();

	
	if (anchoredToSprite_) {

		size_.set(spriteRenderer_->getTexture()->width(), spriteRenderer_->getTexture()->height());
	}
	

	collider_.w = size_.getX() * transform_->getGlobalScale().getX();
	collider_.h = size_.getY() * transform_->getGlobalScale().getY();
}

void BoxCollider::setPosOffset(Vector2D newPosOffset) {
	posOffset_ = newPosOffset;
}

void BoxCollider::setSize(Vector2D newSizOffset) {
	size_ = newSizOffset;
}

bool BoxCollider::isCursorOver() {
	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	
	SDL_Rect mouseRect = build_sdlrect(mousePos, 1, 1);
	
	return SDL_HasIntersection(&collider_, &mouseRect);
}