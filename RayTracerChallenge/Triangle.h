#pragma once

#include "Shape.h"
#include <math.h>

struct Triangle : public Shape{

	Tuple p1;
	Tuple p2;
	Tuple p3;

	Tuple e1;
	Tuple e2;

	Tuple normal;

	Triangle(const Tuple& _p1, const Tuple _p2, const Tuple _p3);

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};

struct SmoothTriangle : public Shape {

	Tuple p1;
	Tuple p2;
	Tuple p3;

	Tuple n1;
	Tuple n2;
	Tuple n3;

	Tuple e1;
	Tuple e2;

	SmoothTriangle(const Tuple& _p1, const Tuple _p2, const Tuple _p3, const Tuple _n1, const Tuple _n2, const Tuple _n3);

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal([[maybe_unused]] const Tuple& objectPoint, const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;
};