#pragma once

#include "Matrix.h"
#include "Material.h"
#include "Tuple.h"

class Shape {
public:

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape(Tuple _origin) : origin(_origin) {}
};