#include "Transform.h"

Transform& 
Transform::operator+(const Transform& t) {
	pos = pos + t.pos;
	scale = scale + t.scale;
	angle += t.angle;
}