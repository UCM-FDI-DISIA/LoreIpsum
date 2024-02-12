// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cassert>
#include <cmath>
#include <ostream>

/*
 * A class implementing a 2-dimensional vector and corresponding
 * operations. All operations generate new Vector2D, they do not
 * modify the vectors on which they operate. The only methods that
 * modify the state are the different setters (and operator=).
 *
 */
class Vector2D {
public:

	// various constructors
	Vector2D() noexcept :
			x_(), y_() {
	}

	Vector2D(const Vector2D &v) noexcept :
			x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(Vector2D &&v) noexcept :
			x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(float x, float y) noexcept :
			x_(x), y_(y) {
	}

	~Vector2D() {
	}

	// various getters
	inline float getX() const {
		return x_;
	}

	inline float getY() const {
		return y_;
	}

	// various setters
	inline void setX(float x) {
		x_ = x;
	}

	inline void setY(float y) {
		y_ = y;
	}

	inline void set(float x, float y) {
		x_ = x;
		y_ = y;
	}

	inline void set(const Vector2D &v) {
		x_ = v.x_;
		y_ = v.y_;
	}

	// copy assignment
	inline Vector2D& operator=(const Vector2D &v) noexcept {
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	// v[0] is the first coordinate and v[1] is the second
	inline float& operator[](int i) noexcept {
		assert(i == 0 || i == 1);
		return i == 0 ? x_ : y_;
	}

	// v[0] is the first coordinate and v[1] is the second
	inline const float& operator[](int i) const noexcept {
		assert(i == 0 || i == 1);
		return i == 0 ? x_ : y_;
	}


	// ** various operations

	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2));
	}

	// vector in the same direction of length 1
	inline Vector2D normalize() const {
		return *this / magnitude();
	}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe) -- which the case when working with SDL.
	//
	Vector2D rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle).normalize() == v.normalize()
	//
	float angle(const Vector2D &v) const;

	// vector subtraction
	inline Vector2D operator-(const Vector2D &v) const {
		return Vector2D(x_ - v.x_, y_ - v.y_);
	}

	// vector addition
	inline Vector2D operator+(const Vector2D &v) const {
		return Vector2D(x_ + v.x_, y_ + v.y_);
	}

	// multiplication by constant (scaling)
	inline Vector2D operator*(float d) const {
		return Vector2D(x_ * d, y_ * d);
	}

	// division by constant (scaling)
	inline Vector2D operator/(float d) const {
		return Vector2D(x_ / d, y_ / d);
	}

	// scalar multiplication
	inline float operator *(const Vector2D &d) const {
		return d.x_ * x_ + d.y_ * y_;
	}

private:
	float x_;  // first coordinate
	float y_;  // second coordinate
};

// needed for printing a value of type Vector2D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream &os, const Vector2D &v);
