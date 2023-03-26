#pragma once

#include "Shape.h"
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

	void UVmap(const Tuple& p, double* u, double* v) const {

		if (maximum - EPSILON <= p.y) {
			//TODO: fix after cubes
			*u = fmod((p.x + 1.f), 2.f) / 2.f;
			*v = fmod((1.f - p.z), 2.f) / 2.f;

			return;
		}

		auto theta = atan2(p.x, p.z);
		auto rawU = theta / (2 * acos(-1));

		// we can scale u by 2 * pi to make the checker pattern square, but should I?
		*u = 1 - (rawU + 0.5);
		*v = fmod(p.y, 1);

		if (*v < 0.0) {
			*v += 1;
		}
	}
};
