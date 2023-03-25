#pragma once
#include "Shape.h"
#include "Helper.h"
#include <algorithm>    // std::swap
#include <iostream>
#include <cmath>
#include <climits>

class Cube : public Shape {

public:
	
	struct MinMaxPoint {
		double tMin = INT_MAX, tMax = INT_MIN;
	};

	Cube();
	void checkAxis(MinMaxPoint& value, double origin, double direction)const;

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1) override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;


};