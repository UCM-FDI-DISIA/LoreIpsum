// This file is part of the course TPV2@UCM - Samir Genaim

#include "Collisions.h"

bool Collisions::collidesWithRotation(const Vector2D &o1Pos, float o1Width,
		float o1Height, float o1Rot, const Vector2D &o2Pos, float o2Width,
		float o2Height, float o2Rot) {
	Vector2D Ac = o1Pos + Vector2D(o1Width / 2.0f, o1Height / 2.0f);

	float angleA = o1Rot;

	Vector2D Alu = Ac
			+ Vector2D(-o1Width / 2.0f, -o1Height / 2.0f).rotate(angleA);
	Vector2D Aru = Ac
			+ Vector2D(o1Width / 2.0f, -o1Height / 2.0f).rotate(angleA);
	Vector2D All = Ac
			+ Vector2D(-o1Width / 2.0f, o1Height / 2.0f).rotate(angleA);
	Vector2D Arl = Ac
			+ Vector2D(o1Width / 2.0f, o1Height / 2.0f).rotate(angleA);

	float angleB = o2Rot;

	Vector2D Bc = o2Pos + Vector2D(o2Width / 2.0f, o2Height / 2.0f);

	Vector2D Blu = Bc
			+ Vector2D(-o2Width / 2.0f, -o2Height / 2.0f).rotate(angleB);
	Vector2D Bru = Bc
			+ Vector2D(o2Width / 2.0f, -o2Height / 2.0f).rotate(angleB);
	Vector2D Bll = Bc
			+ Vector2D(-o2Width / 2.0f, o2Height / 2.0f).rotate(angleB);
	Vector2D Brl = Bc
			+ Vector2D(o2Width / 2.0f, o2Height / 2.0f).rotate(angleB);

	return PointInRectangle(Alu, Aru, All, Arl, Blu)
			|| PointInRectangle(Alu, Aru, All, Arl, Bru)
			|| PointInRectangle(Alu, Aru, All, Arl, Bll)
			|| PointInRectangle(Alu, Aru, All, Arl, Brl)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Alu)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Aru)
			|| PointInRectangle(Blu, Bru, Bll, Brl, All)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Arl);
}

bool Collisions::PointInRectangle(const Vector2D &A, const Vector2D &B,
		const Vector2D &C, const Vector2D &D, const Vector2D &P) {
	if (PointInTriangle(A, B, C, P))
		return true;
	if (PointInTriangle(A, C, D, P))
		return true;
	return false;
}

bool Collisions::PointInTriangle(const Vector2D &A, const Vector2D &B,
		const Vector2D &C, const Vector2D &P) {

	// Compute vectors
	Vector2D v0 = C - A;
	Vector2D v1 = B - A;
	Vector2D v2 = P - A;

	// Compute dot products
	float dot00 = v0 * v0;
	float dot01 = v0 * v1;
	float dot02 = v0 * v2;
	float dot11 = v1 * v1;
	float dot12 = v1 * v2;

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	if (u >= 0 && v >= 0 && (u + v) < 1) {
		return true;
	} else {
		return false;
	}
}

bool Collisions::collides(const Vector2D &o1Pos, float o1Width, float o1Height,
		const Vector2D &o2Pos, float o2Width, float o2Height) {

	// o1 completely to the left of o2, or vice versa
	if (o1Pos.getX() + o1Width < o2Pos.getX()
			|| o2Pos.getX() + o2Width < o1Pos.getX()) {
		return false;
	}

	// o1 completely to the top of o2, or vice versa
	if (o1Pos.getY() + o1Height < o2Pos.getY()
			|| o2Pos.getY() + o2Height < o1Pos.getY()) {
		return false;
	}

	return true;
}
