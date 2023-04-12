#pragma once
#include "Helper.h"
#include "Shape.h"
#include <math.h>
#include <cmath>

struct Plane : public Shape{

	Plane();

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;

	void UVmap(const Tuple& p, double* u, double* v) const override;

};