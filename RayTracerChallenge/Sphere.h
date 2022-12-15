#pragma once

#include "Shape.h"
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"

class Sphere : public Shape {

public:
	Sphere() : Shape(Tuple::point(0, 0, 0)) {}

	bool operator==(const Sphere& other) const;
};