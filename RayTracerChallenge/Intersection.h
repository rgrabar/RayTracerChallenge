#pragma once

#include <vector>
#include <algorithm>
#include <optional>
#include <functional>

#include "Ray.h"
#include "Sphere.h"

class Intersection;

std::vector<Intersection *> intersections;

class Intersection {
public:

	// di ga je hit
	float t;
	const void* s;

	Intersection(float _t, const void* _s) : t(_t), s(_s) {
			
	}

	inline static void sortIntersections() {
		//std::sort(intersections.begin(), intersections.end(), Intersections::compareByLength);
		std::sort(intersections.begin(), intersections.end(), [](const Intersection* a, const Intersection* b)-> bool {
			return a->t < b->t;
			});
	}

	inline static Intersection* hit() {
		sortIntersections();
		
		for (auto& x : intersections) {
			if (x->t >= 0)
				return x;
		}
		
		return nullptr;
	}

};

//TODO: not sure if this should return intersect objects
std::vector<Intersection> intersection(Ray ray, const void* s) {

	auto sphereToRay = ray.origin - Tuple::point(0, 0, 0);
	auto a = ray.direction.dotProduct(ray.direction);
	auto b = 2 * ray.direction.dotProduct(sphereToRay);
	auto c = sphereToRay.dotProduct(sphereToRay) - 1;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return {};

	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);

	//TODO: not sure if I should add each record 
	//intersections.emplace_back(t1, s);
	//intersections.emplace_back(t2, s);

	/*std::vector<Intersection> retInter;
	retInter.emplace_back(t1, s);
	retInter.emplace_back(t2, s);
	*/
	return { {t1, s}, {t2, s} };
}
