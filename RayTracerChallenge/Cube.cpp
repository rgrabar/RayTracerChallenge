#include "Cube.h"


Cube::Cube() : Shape(Tuple::point(0, 0, 0)) {}

void Cube::checkAxis(MinMaxPoint& value, double origin, double direction)const {
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

Intersections Cube::intersect(const Ray& ray)const {

	MinMaxPoint tmpMinMax;

	checkAxis(tmpMinMax, ray.origin.x, ray.direction.x);
	auto [xTmin, xTmax] = tmpMinMax;

	checkAxis(tmpMinMax, ray.origin.y, ray.direction.y);
	auto [yTmin, yTmax] = tmpMinMax;

	checkAxis(tmpMinMax, ray.origin.z, ray.direction.z);
	auto [zTmin, zTmax] = tmpMinMax;

	auto tmin = std::fmax(xTmin, std::fmax(yTmin, zTmin));
	auto tmax = std::fmin(xTmax, std::fmin(yTmax, zTmax));

	if (tmin > tmax)
		return{};

	Intersections inter;
	inter.intersections.insert(new Intersection(tmin, this));
	inter.intersections.insert(new Intersection(tmax, this));

	return inter;
}

Tuple Cube::objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr)const {
	auto maxc = std::fmax(fabs(objectPoint.x), fabs(std::fmax(fabs(objectPoint.y), fabs(objectPoint.z))));
	if (epsilonEqual(maxc, fabs(objectPoint.x))) {
		return Tuple::vector(objectPoint.x, 0, 0);
	}
	else if (epsilonEqual(maxc, fabs(objectPoint.y))) {
		return Tuple::vector(0, objectPoint.y, 0);
	}
	return Tuple::vector(0, 0, objectPoint.z);
}

BoundingBox Cube::boundsOf(bool update = false) {
	return BoundingBox(Tuple::point(-1, -1, -1), Tuple::point(1, 1, 1));
}

inline void Cube::divide(int threashold = 1)const {
	return;
}

inline bool Cube::includes(const Shape* s)const {
	return this == s;
}

inline void Cube::setMaterial(const Material& s) {
	material = s;
}