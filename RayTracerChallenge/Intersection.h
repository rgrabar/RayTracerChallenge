#pragma once

#include <vector>
#include <algorithm>
#include <optional>
#include <functional>
#include <set>
#include "Helper.h"

class Intersection {
public:

	// di ga je hit
	double t;
	const void* s;

	Intersection(double _t, const void* _s);

};

const auto cmp = [](const Intersection* lhs, const Intersection* rhs) {
	return lhs->t <= rhs->t;
};

class Intersections {
public:
	Intersections() {};
	Intersections(const std::multiset<Intersection*, decltype(cmp)>& i) : intersections(i) {

	}

	Intersection* hit()const;
	std::multiset<Intersection*, decltype(cmp)> intersections;
};

