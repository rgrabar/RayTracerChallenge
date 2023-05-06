#include "Plane.h"

Plane::Plane() : Shape(Point(0, 0, 0)) {}

Intersections Plane::intersect(const Ray& ray)const {
	if (fabs(ray.direction.y) < EPSILON)
		return {};
	double t = -ray.origin.y / ray.direction.y;

	Intersection* i1 = new Intersection(t, this);

	Intersections inter;
	inter.intersections.insert(i1);

	return inter;
}
Tuple Plane::objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit)const {
	return Vector(0.0, 1.0, 0.0);
}

BoundingBox Plane::boundsOf([[maybe_unused]] bool update) {
	return BoundingBox(Point(-INFINITY, 0, -INFINITY), Point(INFINITY, 0, INFINITY));
}

void Plane::divide([[maybe_unused]] int threashold) {
	return;
}

bool Plane::includes(const Shape* s)const {
	return this == s;
}

void Plane::setMaterial(const Material& s) {
	material = s;
}

void Plane::UVmap(const Tuple& p, double* u, double* v) const {

	*u = fmod(p.x, 1);
	*v = fmod(p.z, 1);

	if (*u < 0.0)
		*u += 1;

	if (*v < 0.0)
		*v += 1;
}