#pragma once

#include "Shape.h"
#include "Helper.h"
#include <iostream>

class Cylinder : public Shape {

public:
	double minimum = -INFINITY;
	double maximum = INFINITY;
	bool closed = false;

	Cylinder();

	bool checkCap(const Ray& ray, double t)const;
	void intersectCaps(const Ray& ray, Intersections& inter)const;
	
	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf(bool update = false)override;
	void divide(int threashold = 1)const override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};
