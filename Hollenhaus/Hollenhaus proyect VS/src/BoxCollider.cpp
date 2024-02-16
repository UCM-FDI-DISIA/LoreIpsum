#pragma once
#include "BoxCollider.h"
#include "game/Manager.h"

BoxCollider::BoxCollider() :
	transform_(),
	spriteRenderer_(),
	collider_(),
	offset_() 
{
	initComponent();
}

void BoxCollider::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
	spriteRenderer_ = mngr_->getComponent<SpriteRenderer>(ent_);

	if (spriteRenderer_ != nullptr) {
		collider_.h = spriteRenderer_->getTexture()->height();
		collider_.w = spriteRenderer_->getTexture()->width();
	}
}

void BoxCollider::update() {
	collider_.x = transform_->getGlobalPos().getX() + offset_.getX();
	collider_.y = transform_->getGlobalPos().getY() + offset_.getY();
}