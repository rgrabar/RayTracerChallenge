#pragma once

#include <vector>
#include <algorithm>
#include <optional>
#include <functional>

#include "Ray.h"
#include "Sphere.h"
#include "Shape.h"
#include <set>

class Intersection {
public:

	// di ga je hit
	float t;
	Shape* s;

	Intersection(float _t, Shape* _s);

};

const auto cmp = [](const Intersection* lhs, const Intersection* rhs) {
	return lhs->t < rhs->t;
};

class Intersections {
public:
	Intersections() {};
	Intersections(const std::set<Intersection*, decltype(cmp)>& i) : intersections(i) {

	}

	Intersection* hit();
	std::set<Intersection*, decltype(cmp)> intersections;
};

//TODO: not sure if this should return intersect objects

inline std::vector<Intersection> intersect(const Ray& ray, Shape& s) {

	auto rayCalc = ray.transform(s.transform.inverse());
	auto shapeToRay = rayCalc.origin - Tuple::point(0, 0, 0);
	auto a = rayCalc.direction.dotProduct(rayCalc.direction);
	auto b = 2 * rayCalc.direction.dotProduct(shapeToRay);
	auto c = shapeToRay.dotProduct(shapeToRay) - 1;

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
	return { {t1, &s}, {t2, &s} };
}


