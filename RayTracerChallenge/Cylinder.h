#pragma once

#include "BoundingBox.h"
#include "Intersection.h"
#include "Shape.h"
#include "Tuple.h"
#include "Helper.h"
#include <iostream>
#include <cmath>

class Cylinder : public Shape {

public:
	double minimum = -INFINITY;
	double maximum = INFINITY;
	bool closed = false;

	Cylinder();

	bool checkCap(const Ray& ray, double t)const;
	void intersectCaps(const Ray& ray, Intersections& inter)const;
	
	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1) override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;

	void UVmap(const Tuple& p, double* u, double* v) const override;
};
