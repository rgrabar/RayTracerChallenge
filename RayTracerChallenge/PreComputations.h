#pragma once

#include "Shape.h"
#include "Intersection.h"
#include "Tuple.h"
#include "Helper.h"
#include <vector>

struct Precomputations {

	Ray ray;
	// vectors
	Tuple eyev, normalv, reflectv;
	// points
	Tuple point, overPoint, underPoint;
	Shape* shape;
	bool inside;
	double t = 0;
	double n1 = 0, n2 = 0;

	std::vector<Shape*> container;

	Precomputations() : ray(Point(0, 0, 0), Vector(0, 0, 0)){}
	Precomputations(const Intersection& _intersection, const Ray& _ray, const Intersections& intersections = {});
	double schlick() const;
};