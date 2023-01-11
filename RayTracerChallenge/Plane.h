#pragma once
#include "Shape.h"
#include <math.h>
#include "Helper.h"

class Plane : public Shape{
public:
	Plane() : Shape(Tuple::point(0, 0, 0)) {}

	inline std::vector<Intersection> intersect(const Ray& ray) {
		if (fabs(ray.direction.y) < EPSILON)
			return {};
		double t = -ray.origin.y / ray.direction.y;
		return { {t, this} };
	}
	Tuple objectNormal(const Tuple& worldPoint) {
		return Tuple::vector(0.0, 1.0, 0.0);
	}
};