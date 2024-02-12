// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "Vector2D.h"

/*
 *
 */
class Collisions {
public:
	// virtual ~Collisions();

	// checks if two boxes o1 and o2 collides
	static bool collides( //
			const Vector2D &o1Pos, float o1Width, float o1Height, //
			const Vector2D &o2Pos, float o2Width, float o2Height);

	// checks if two boxed o1 and o2 collides, taking into account the rotation of both
	static bool collidesWithRotation( //
			const Vector2D &o1Pos, float o1Width, float o1Height, float o1Rot, //
			const Vector2D &o2Pos, float o2Width, float o2Height, float o2Rot);

private:
	Collisions() = delete;

	// checks if the point P is in the triangle defined by A,B,C
	static bool PointInTriangle(const Vector2D &A, const Vector2D &B,
			const Vector2D &C, const Vector2D &P);

	// checks if the point P is in the rectangle defined by the rectangle
	//
	//     A --- B
	//     |     |
	//     |     |
	//     D --- C
	//
	static bool PointInRectangle(const Vector2D &A, const Vector2D &B,
			const Vector2D &C, const Vector2D &D, const Vector2D &P);

};
