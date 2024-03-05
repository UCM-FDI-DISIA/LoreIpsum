#include "Transform.h"
#include "Manager.h"

void
Transform::update() {
	if (isChild_) {
		globalScale_ = relativeScale_ * parent_->globalScale_.magnitude();
	}
}

void 
Transform::increaseLayer() {
	ent_->setLayer(parent_->ent_->getLayer() + layerToIncrease);
	for (auto it = childs_.begin(); it != childs_.end(); ++it) {
		(*it)->increaseLayer();
	}
}

void
Transform::addParent(Transform* p) {
	if (!isChild_) {
		parent_ = p;
		parent_->addChild(this);
		relativePos_ = globalPos_ - parent_->getGlobalPos(); // Pos relativa al padre
		relativeAngle_ = globalAngle_ - parent_->globalAngle_;
		isChild_ = true;
	}
}

void
Transform::removeParent() {
	if (isChild_) {
		parent_->removeChild(this);
		parent_ = nullptr;
		relativePos_ = Vector2D(0, 0);
		isChild_ = false;
	}
}

std::list<Transform*> 
Transform::getChilds() {
	return childs_;
}

Vector2D 
Transform::getGlobalPos() {
	if (isChild_)
		return parent_->getGlobalPos() + relativePos_;
	else
		return globalPos_;
}

Vector2D& Transform::getGlobalScale()
{
	return globalScale_;
}

float& Transform::getGlobalAngle()
{
	return globalAngle_;
}

Vector2D& Transform::getRelativePos()
{
	return relativePos_;
}

Vector2D& Transform::getRelativeScale()
{
	return relativeScale_;
}

float& Transform::getRelativeAngle()
{
	return relativeAngle_;
}

void
Transform::setGlobalPos(Vector2D& pos) {
	globalPos_ = pos;
	if (isChild_)
		relativePos_ = globalPos_ - parent_->getGlobalPos();
}

void Transform::setGlobalAngle(float angle)
{
	globalAngle_ = angle;
	if (isChild_)
		relativeAngle_ = globalAngle_ - parent_->globalAngle_;
}

Transform* Transform::getParent()
{
	return parent_;
}

Transform&
Transform::operator+(const Transform& t) {
	globalPos_ = globalPos_ + t.globalPos_;
	globalScale_ = globalScale_ + t.globalScale_;
	globalAngle_ += t.globalAngle_;
	vel_ = vel_ + t.vel_;

	return *this;
}

Transform&
Transform::operator-(const Transform& t) {
	globalPos_ = globalPos_ - t.globalPos_;
	globalScale_ = globalScale_ - t.globalScale_;
	globalAngle_ -= t.globalAngle_;
	vel_ = vel_ - t.vel_;

	return *this;
}

Transform&
Transform::operator=(const Transform& t) {
	globalPos_ = t.globalPos_;
	globalScale_ = t.globalScale_;
	globalAngle_ = t.globalAngle_;
	vel_ = t.vel_;

	return *this;
}

void 
Transform::addChild(Transform* c) {
	childs_.emplace_back(c);
}

void 
Transform::removeChild(Transform* c) {
	childs_.remove(c);
}
