#pragma once

#include "Shape.h"
#include "Intersection.h"
#include "Tuple.h"
#include "Helper.h"
#include <vector>

class Precomputations {
public:

	Ray ray;
	Tuple point, eyev, normalv, reflectv;
	Tuple overPoint, underPoint;
	Shape* shape;
	bool inside;
	double t = 0;
	double n1 = 0, n2 = 0;

	std::vector<Shape*> container;

	Precomputations();
	// TODO: can i remove the default?
	Precomputations(const Intersection& _intersection, const Ray& _ray, const Intersections& intersections = {});
	double schlick() const;
};