#include "Transform.h"

void
Transform::addParent(Transform* p) {
	if (!isChild_) {
		parent_ = p;
		pos_ = pos_ - parent_->pos_; // Pos realtiva al padre
		isChild_ = true;
	}
}

void
Transform::update() {
	if (isChild_);
		// Movimiento con padre
	else;
		// Sin padre
}

Transform& 
Transform::operator+(const Transform& t) {
	pos_ = pos_ + t.pos_;
	scale_ = scale_ + t.scale_;
	angle_ += t.angle_;
	vel_ = vel_ + t.vel_;

	return *this;
}

Transform&
Transform::operator-(const Transform& t) {
	pos_ = pos_ - t.pos_;
	scale_ = scale_ - t.scale_;
	angle_ -= t.angle_;
	vel_ = vel_ - t.vel_;

	return *this;
}

Transform&
Transform::operator=(const Transform& t) {
	pos_ = t.pos_;
	scale_ = t.scale_;
	angle_ = t.angle_;
	vel_ = t.vel_;

	return *this;
}