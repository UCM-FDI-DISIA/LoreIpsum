#include <../pchs/pch.h>

#pragma once
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "../managers/Manager.h"
#include "Transform.h"
#include "../ColliderRender.h"
#include "../../../sdlutils/InputHandler.h"
#include "../../../utils/Collisions.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "../../../utils/Vector2D.h"

BoxCollider::BoxCollider() : BoxCollider(Vector2D(0, 0), Vector2D(1, 1))
{}

BoxCollider::BoxCollider(Vector2D posOffset, Vector2D size) :
	transform_(),
	spriteRenderer_(),
	anchoredToSprite_(false),
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
	vertices[1] = transform_->getGlobalPos();
	vertices[2] = vertices[1] + Vector2D(size_.getX(), vertices[1].getY());
	vertices[3] = vertices[1] + size_;
	vertices[4] = vertices[1] + Vector2D(vertices[1].getX(), size_.getY());*/



	if (spriteRenderer_ != nullptr) {
		size_.set(spriteRenderer_->getTexture()->width(), spriteRenderer_->getTexture()->height());
		anchoredToSprite_ = true;
	}
	else
	{
		anchoredToSprite_ = false;
	}


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
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	
	SDL_Rect mouseRect = build_sdlrect(mousePos, 1, 1);

	return SDL_HasIntersection(&collider_, &mouseRect);
}

bool BoxCollider::PointOver(Vector2D point)
{
	SDL_Rect mouseRect = build_sdlrect(point, 1, 1);

	return SDL_HasIntersection(&collider_, &mouseRect);
}