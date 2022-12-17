#pragma once

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Tuple.h"

class Precomputations {
public:

	Ray ray;
	float t;
	Shape* shape;
	Tuple point, eyev, normalv;
	bool inside;

	Precomputations(const Intersection& _intersection, const Ray& _ray);
};