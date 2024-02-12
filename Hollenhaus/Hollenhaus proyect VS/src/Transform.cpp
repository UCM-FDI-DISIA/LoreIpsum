#include "Transform.h"

Transform& 
Transform::operator+(const Transform& t) {
	pos = pos + t.pos;
	scale = scale + t.scale;
	angle += t.angle;

	return *this;
}

Transform&
Transform::operator=(const Transform& t) {
	pos = t.pos;
	scale = t.scale;
	angle = t.angle;

	return *this;
}