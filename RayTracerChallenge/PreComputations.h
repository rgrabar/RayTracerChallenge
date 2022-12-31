#pragma once

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Tuple.h"
#include "Helper.h"
#include <vector>

class Precomputations {
public:

	Ray ray;
	double t = 0;
	Shape* shape;
	Tuple point, eyev, normalv, reflectv;
	bool inside;
	Tuple overPoint, underPoint;
	double n1 = 0, n2 = 0;

	std::vector<Shape*> container;

	Precomputations();
	Precomputations(const Intersection& _intersection, const Ray& _ray, const Intersections& intersections = {});
	double schlick() const;
};