#pragma once

#include "Matrix.h"
#include "Material.h"
#include "Tuple.h"
#include "Intersection.h"
#include "Ray.h"

class Shape {
public:

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape() :origin(Tuple::point(0, 0, 0)) {}
	Shape(Tuple _origin) : origin(_origin) {}


	//TODO: not sure if this should return intersect objects

	inline virtual std::vector<Intersection> intersect(const Ray& ray) = 0;
	inline virtual Tuple normalAt(const Tuple& worldPoint)const = 0;

};