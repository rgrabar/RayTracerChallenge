#pragma once

#include <iostream>
#include "Helper.h"
#include "Matrix.h"
#include "Shape.h"
#include "Tuple.h"

class Cone : public Shape {

public:
	double minimum = -INFINITY;
	double maximum = INFINITY;
	bool closed = false;

	Cone();

	bool checkCap(const Ray& ray, const double t, const double radius)const;
	void intersectCaps(const Ray& ray, Intersections& inter)const;
	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf(bool update = false) override;
	void divide(int threashold = 1) override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};
