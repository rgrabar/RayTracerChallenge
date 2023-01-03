#pragma once
#include "Shape.h"
#include "Helper.h"
#include <algorithm>    // std::swap
#include <iostream>
#include <cmath>

class Cube : public Shape {

public:
	
	struct MinMaxPoint {
		double tMin = INT_MAX, tMax = INT_MIN;
	};

	Cube() : Shape(Tuple::point(0, 0, 0)) {}

	inline std::vector<Intersection> intersect(const Ray& ray) {

		MinMaxPoint tmp;
		
		checkAxis(tmp, ray.origin.x, ray.direction.x);
		auto [xTmin, xTmax] = tmp;

		checkAxis(tmp, ray.origin.y, ray.direction.y);
		auto [yTmin, yTmax] = tmp;

		checkAxis(tmp, ray.origin.z, ray.direction.z);
		auto [zTmin, zTmax] = tmp;

		auto tmin = std::fmax( xTmin, std::fmax(yTmin, zTmin));
		auto tmax = std::fmin(xTmax, std::fmin(yTmax, zTmax ));

		if (tmin > tmax)
			return{};

		return { {tmin, this}, {tmax, this} };
	}

	void checkAxis(MinMaxPoint& value, double origin, double direction) {
		auto tminNumerator = (-1 - origin);
		auto tmaxNumerator = (1 - origin);

		if (fabs(direction) >= EPSILON) {
			value.tMin = tminNumerator / direction;
			value.tMax = tmaxNumerator / direction;
		}
		else {
			value.tMin = tminNumerator * INFINITY;
			value.tMax = tmaxNumerator * INFINITY;
		}

		if (value.tMin > value.tMax) {
			auto tmp = value.tMax;
			value.tMax = value.tMin;
			value.tMin = tmp;
		}
	}

	Tuple normalAt(const Tuple& objectPoint) {
		auto maxc = std::fmax(fabs(objectPoint.x), fabs(std::fmax(fabs(objectPoint.y), fabs(objectPoint.z))));
		if (epsilonEqual(maxc, fabs(objectPoint.x))) {
			return Tuple::vector(objectPoint.x, 0, 0);
		}
		else if (epsilonEqual(maxc, fabs(objectPoint.y))) {
			return Tuple::vector(0, objectPoint.y, 0);
		}
		return Tuple::vector(0, 0, objectPoint.z);
	}

};