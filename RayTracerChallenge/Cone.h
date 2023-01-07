#pragma once

#include "Shape.h"
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"
#include <iostream>
#include "Helper.h"

class Cone : public Shape {

public:
	double minimum = -INFINITY;
	double maximum = INFINITY;
	bool closed = false;

	Cone() : Shape(Tuple::point(0, 0, 0)) {}

	bool checkCap(const Ray& ray, const double t, const double radius) {
		auto x = ray.origin.x + t * ray.direction.x;
		auto z = ray.origin.z + t * ray.direction.z;

		return(x * x + z * z) <= radius;
	}

	void intersectCaps(const Ray& ray, std::vector<Intersection>& inter) {
		if (!closed || epsilonEqual(ray.direction.y, 0)) {
			return;
		}
		auto t = (minimum - ray.origin.y) / ray.direction.y;

		if (checkCap(ray, t, std::fabs(minimum))) {
			inter.emplace_back(t, this);
		}

		t = (maximum - ray.origin.y) / ray.direction.y;

		if (checkCap(ray, t, std::fabs(maximum))) {
			inter.emplace_back(t, this);
		}
		return;
	}

	inline std::vector<Intersection> intersect(const Ray& ray) {

		bool cylinderBodyIntersection = true;
		auto a = ray.direction.x * ray.direction.x - ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
		auto b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y + 2 * ray.origin.z * ray.direction.z;
		auto c = ray.origin.x * ray.origin.x -ray.origin.y * ray.origin.y + ray.origin.z * ray.origin.z;
		auto disc = b * b - 4 * a * c;

		if (epsilonEqual(a, 0) && epsilonEqual(b, 0)) {
			cylinderBodyIntersection = false;
		}

		if (disc < 0)
			cylinderBodyIntersection = false;

		std::vector<Intersection> inter;

		if (cylinderBodyIntersection) {

			if (epsilonEqual(a, 0) && !epsilonEqual(b, 0)) {
				auto t = -c / (2 * b);
				inter.emplace_back(t, this);
			}
			else {
				auto t0 = (-b - sqrt(disc)) / (2 * a);
				auto t1 = (-b + sqrt(disc)) / (2 * a);

				if (t0 > t1) {
					std::swap(t0, t1);
				}

				auto y0 = ray.origin.y + t0 * ray.direction.y;
				auto y1 = ray.origin.y + t1 * ray.direction.y;


				if (minimum < y0 && y0 < maximum) {
					inter.emplace_back(t0, this);
				}

				if (minimum < y1 && y1 < maximum) {
					inter.emplace_back(t1, this);
				}
			}

		}

		intersectCaps(ray, inter);

		return inter;
	}

	Tuple normalAt(const Tuple& objectPoint) {
		auto dist = objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z;
		if (dist < 1 && objectPoint.y >= maximum - EPSILON)
			return Tuple::vector(0, 1, 0);

		else if (dist < 1 && objectPoint.y <= minimum + EPSILON)
			return Tuple::vector(0, -1, 0);

		auto y = sqrt(objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z);

		if (objectPoint.y > 0)
			y *= -1;

		return Tuple::vector(objectPoint.x, y, objectPoint.z);
	}
};
