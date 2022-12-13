#pragma once

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Tuple.h"

class Precomputations {
public:

	Ray ray;
	float t;
	const void* shape;
	Tuple point, eyev, normalv;
	bool inside;

	Precomputations(Intersection& _intersection, Ray& _ray);
	
};