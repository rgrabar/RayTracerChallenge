#include "Plane.h"

Plane::Plane() : Shape(Tuple::point(0, 0, 0)) {}

Intersections Plane::intersect(const Ray& ray)const {
	if (fabs(ray.direction.y) < EPSILON)
		return {};
	double t = -ray.origin.y / ray.direction.y;

	Intersection* i1 = new Intersection(t, this);

	Intersections inter;
	inter.intersections.insert(i1);

	return inter;
}
Tuple Plane::objectNormal(const Tuple& worldPoint, const Intersection* hit)const {
	return Tuple::vector(0.0, 1.0, 0.0);
}

BoundingBox Plane::boundsOf(bool update) {
	return BoundingBox(Tuple::point(-INFINITY, 0, -INFINITY), Tuple::point(INFINITY, 0, INFINITY));
}

void Plane::divide(int threashold) {
	return;
}

bool Plane::includes(const Shape* s)const {
	return this == s;
}

void Plane::setMaterial(const Material& s) {
	material = s;
}