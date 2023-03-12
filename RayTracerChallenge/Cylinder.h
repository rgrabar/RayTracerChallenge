#pragma once

#include "Shape.h"
#include "Helper.h"
#include <iostream>

class Cylinder : public Shape {

public:
	double minimum = -INFINITY;
	double maximum = INFINITY;
	bool closed = false;

	Cylinder() : Shape(Tuple::point(0, 0, 0)) {}

	bool checkCap(const Ray& ray, double t) {
		auto x = ray.origin.x + t * ray.direction.x;
		auto z = ray.origin.z + t * ray.direction.z;

		return(x * x + z * z) <= 1;
	}

	void intersectCaps(const Ray& ray, Intersections& inter) {
		if (!closed || epsilonEqual(ray.direction.y, 0)) {
			return;
		}
		auto t = (minimum - ray.origin.y) / ray.direction.y;

		if (checkCap(ray, t)) {
			inter.intersections.insert(new Intersection(t, this));
		}
		
		t = (maximum - ray.origin.y) / ray.direction.y;

		if (checkCap(ray, t)) {
			inter.intersections.insert(new Intersection(t, this));
		}
		return;
	}

	inline Intersections intersect(const Ray& ray) {

		bool cylinderBodyIntersection = true;
		auto a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;

		if (epsilonEqual(a, 0)) {
			cylinderBodyIntersection = false;
		}

		auto b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
		auto c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
		auto disc = b * b - 4 * a * c;

		if (disc < 0)
			cylinderBodyIntersection = false;
		
		Intersections inter;

		if (cylinderBodyIntersection) {

			auto t0 = (-b - sqrt(disc)) / (2 * a);
			auto t1 = (-b + sqrt(disc)) / (2 * a);

			if (t0 > t1) {
				std::swap(t0, t1);
			}

			auto y0 = ray.origin.y + t0 * ray.direction.y;
			auto y1 = ray.origin.y + t1 * ray.direction.y;


			if (minimum < y0 && y0 < maximum) {
				inter.intersections.insert(new Intersection(t0, this));
			}

			if (minimum < y1 && y1 < maximum) {
				inter.intersections.insert(new Intersection(t1, this));
			}

		}

		intersectCaps(ray, inter);

		return inter;
	}

	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		auto dist = objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z;
		if (dist < 1 && objectPoint.y >= maximum - EPSILON)
			return Tuple::vector(0, 1, 0);

		else if (dist < 1 && objectPoint.y <= minimum + EPSILON)
			return Tuple::vector(0, -1, 0);

		return Tuple::vector(objectPoint.x, 0, objectPoint.z);
	}

	BoundingBox boundsOf(bool update = false) {
		return BoundingBox(Tuple::point(-1, minimum, -1), Tuple::point(1, maximum, 1));
	}

	inline void divide(int threashold = 1) {
		return;
	}

	inline bool includes(const Shape* s) {
		return this == s;
	}

	inline void setMaterial(const Material& s) {
		material = s;
	}
};
