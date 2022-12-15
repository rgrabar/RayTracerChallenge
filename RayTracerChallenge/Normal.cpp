#include "Normal.h"

Tuple normal_at(const Shape& s, const Tuple& worldPoint) {
	auto objectPoint = s.transform.inverse() * worldPoint;
	auto objectNormal = objectPoint - Tuple::point(0, 0, 0);

	auto worldNormal = s.transform.inverse().transpose() * objectNormal;
	worldNormal.w = 0;

	return (worldNormal.normalize());
}

Tuple reflect(const Tuple& in, const Tuple& normal) {
	return in - normal * 2 * in.dotProduct(normal);
}