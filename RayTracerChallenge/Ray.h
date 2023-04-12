#pragma once
#include "Tuple.h"
#include "Matrix.h"

struct Ray {

	Tuple origin, direction;

	Ray(const Tuple& _origin, const Tuple& _direction) : origin(_origin), direction(_direction){}

	Tuple position(double t)const;
	Ray transform(const Matrix& m)const;
};