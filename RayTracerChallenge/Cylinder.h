#pragma once

#include "Shape.h"
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"
#include <iostream>
#include "Helper.h"

class Cylinder : public Shape {

public:
	Cylinder() : Shape(Tuple::point(0, 0, 0)) {}

	inline std::vector<Intersection> intersect(const Ray& ray) {


		auto a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;

		if (epsilonEqual(a, 0)) {
			return {};
		}

		auto b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
		auto c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
		auto disc = b * b - 4 * a * c;

		if (disc < 0)
			return {};


		return { {1, this} };
	}
	Tuple normalAt(const Tuple& objectPoint) {
		return objectPoint - Tuple::point(0, 0, 0);
	}
};
