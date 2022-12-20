#pragma once

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Tuple.h"
#include "Helper.h"

class Precomputations {
public:

	Ray ray;
	double t;
	Shape* shape;
	Tuple point, eyev, normalv;
	bool inside;
	Tuple overPoint;
	Precomputations(const Intersection& _intersection, const Ray& _ray);
};