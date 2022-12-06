#pragma once

#include <vector>
#include <algorithm>
#include <optional>
#include <functional>

#include "Ray.h"
#include "Sphere.h"
#include <set>

class Intersection {
public:

	// di ga je hit
	float t;
	const void* s;

	Intersection(float _t, const void* _s) : t(_t), s(_s) {

	}

	static Intersection* hit();

};

auto cmp = [](const Intersection* lhs, const Intersection* rhs) {
	return lhs->t < rhs->t;
};

std::set<Intersection*, decltype(cmp)> intersections(cmp);

Intersection* Intersection::hit() {
	//sortIntersections();

	float maxT = INT_MAX;
	Intersection* ret = nullptr;

	for (auto& x : intersections) {
		if (x->t < 0)
			continue;
		if (x->t < maxT) {
			maxT = x->t;
			ret = x;
		}
	}

	if (ret != nullptr)
		return ret;

	return nullptr;
}

//TODO: not sure if this should return intersect objects

template<typename T>
std::vector<Intersection> intersection(Ray ray, const T* s) {

	ray = ray.transform(s->transform.inverse());

	auto sphereToRay = ray.origin - Tuple::point(0, 0, 0);
	auto a = ray.direction.dotProduct(ray.direction);
	auto b = 2 * ray.direction.dotProduct(sphereToRay);
	auto c = sphereToRay.dotProduct(sphereToRay) - 1;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return {};


	//TODO: make the first t the non negative smaller value

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
