#pragma once
#include "BoxCollider.h"
#include "game/Manager.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "game/Manager.h"
#include "game/ColliderRender.h"

BoxCollider::BoxCollider() :BoxCollider(Vector2D(0, 0), Vector2D(1, 1))
{}
BoxCollider::BoxCollider(Vector2D posOffset, Vector2D size) :
	transform_(),
	collider_(),
	posOffset_(posOffset),
	size_(size)
{
	
}

void BoxCollider::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);

	collider_.w = size_.getX();
	collider_.h = size_.getY();


	SpriteRenderer* spriteRenderer = mngr_->getComponent<SpriteRenderer>(ent_);


	if (spriteRenderer != nullptr) {
		size_.set(spriteRenderer->getTexture()->width(), spriteRenderer->getTexture()->height());
	}

#ifdef _DEBUG
	mngr_->addComponent<ColliderRender>(ent_);
#endif // DEBUG

}

void BoxCollider::update() {
	collider_.x = transform_->getGlobalPos().getX() + posOffset_.getX();
	collider_.y = transform_->getGlobalPos().getY() + posOffset_.getY();
}

void BoxCollider::setPosOffset(Vector2D newPosOffset) {
	posOffset_ = newPosOffset;
}

void BoxCollider::setSize(Vector2D newSizOffset) {
	size_ = newSizOffset;
}