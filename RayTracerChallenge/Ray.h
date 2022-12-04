#pragma once
#include "Tuple.h"
#include "Matrix.h"

class Ray {

public:
	Tuple origin, direction;


	Ray(Tuple _origin, Tuple _direction) : origin(_origin), direction(_direction){}

	Tuple position(float t) const;

	Ray transform(const Matrix m);



};