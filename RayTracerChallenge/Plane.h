#pragma once
#include "Shape.h"
#include <math.h>
#include "Helper.h"

class Plane : public Shape{
public:
	Plane() {}

	inline std::vector<Intersection> intersect(const Ray& ray) {
		auto rayCalc = ray.transform(transform.inverse());
		if (fabs(rayCalc.direction.y) < EPSILON)
			return {};
		double t = -rayCalc.origin.y / rayCalc.direction.y;

		return { {t, this} };
	}
	Tuple normalAt(const Tuple& worldPoint) {
		return Tuple::vector(0.0, 1.0, 0.0);
	}
};