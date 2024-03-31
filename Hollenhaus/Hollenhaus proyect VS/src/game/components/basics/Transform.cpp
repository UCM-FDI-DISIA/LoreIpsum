#include "pch.h"
#include "Transform.h"
#include "../managers/Manager.h"


void
Transform::update() {
}

void 
Transform::increaseLayer(int layer) {
	int nextLayer = layer + layerToIncrease;
	ent_->setLayer(nextLayer);
	if(children_.size() > 0){
		for (auto it = children_.begin(); it != children_.end(); ++it) {
			(*it)->increaseLayer(ent_->getLayer());
		}
	}
}

void Transform::setLayerIncrementalInHierarchy(int layer)
{
	
}

void
Transform::addParent(Transform* p) {
	if (!isChild_) {
		parent_ = p;
		parent_->addChild(this);
		relativePos_ = globalPos_ - parent_->getGlobalPos(); // Pos relativa al padre
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

void Transform::killChilds()
{
	for (auto & t : children_)
	{
		t->killChilds();
		t->getEntity()->setAlive(false);
	}

	children_.clear();
}

std::list<Transform*>
Transform::getChildren() {
	return children_;
}

Vector2D 
Transform::getGlobalPos() {
	if (isChild_)
		return parent_->getGlobalPos() + relativePos_;
	else
		return globalPos_;
}


Vector2D Transform::getGlobalScale()
{
	if (isChild_ && parent_ != nullptr)
		return Vector2D(parent_->getGlobalScale().getX() * relativeScale_.getX(),
			parent_->getGlobalScale().getY() * relativeScale_.getY());
	else
		return relativeScale_;

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

void 
Transform::setGlobalAngle(float angle) {
	globalAngle_ = angle;
	if (isChild_)
		relativeAngle_ = globalAngle_ - parent_->globalAngle_;
}

void 
Transform::setGlobalScale(Vector2D s) {
	globalScale_ = s;
	if (isChild_)
		relativeScale_.set(globalScale_.getX() / parent_->globalScale_.getX(), globalScale_.getY() / parent_->globalScale_.getY());
	else
		relativeScale_.set(s);
}

void Transform::setGlobalScale(float x, float y)
{
	globalScale_ = Vector2D(x, y);
	if (isChild_)
		relativeScale_.set(globalScale_.getX() / parent_->globalScale_.getX(), globalScale_.getY() / parent_->globalScale_.getY());
	else
		relativeScale_.set(globalScale_);
}

Transform* 
Transform::getParent() {
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
	children_.emplace_back(c);
}

void 
Transform::removeChild(Transform* c) {
	children_.remove(c);
}
