#include "Transform.h"

void
Transform::update() {
	if (isChild_) {
		globalAngle_ += parent_->globalAngle_;
		globalScale_ = relativeScale_ * parent_->globalScale_.magnitude();
		globalPos_ = parent_->globalPos_ + relativePos_;
	}
}

void
Transform::addParent(Transform* p) {
	if (!isChild_) {
		parent_ = p;
		relativePos_ = globalPos_ - parent_->globalPos_; // Pos relativa al padre
		isChild_ = true;
	}
}

void
Transform::removeParent() {
	if (isChild_) {
		parent_ = nullptr;
		relativePos_ = Vector2D(0, 0);
		isChild_ = false;
	}
}

void 
Transform::setGlobalPos(Vector2D& pos) {
	globalPos_ = pos;
	if (isChild_)
		relativePos_ = globalPos_ - parent_->globalPos_;
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