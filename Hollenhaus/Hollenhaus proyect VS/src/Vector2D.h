#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"



template<class T = double>
class Vector2D {

	T x,y;

public:


	//constructores
	Vector2D() { x = 0; y = 0; };
	Vector2D(T _x,T _y) : x(_x), y(_y){};


	//getters
	T getX()const { return x; };
	T getY()const { return y; };


	//operadores
	Vector2D operator+(const Vector2D& other) const{
		return Vector2D(x + other.x, y + other.y);
	};

	Vector2D operator-(const Vector2D& other)const {
		return Vector2D(x - other.x, y - other.y);
	};

	T operator*(const Vector2D other)const {
		return (x * other.x) +( y * other.y);
	};

	Vector2D operator*(double escalar) {
		return Vector2D(x * escalar, y * escalar);
	}
};



//alias
template <class T = double>
using Point2D = Vector2D<T>;


#endif // !VECTOR2D_H_

