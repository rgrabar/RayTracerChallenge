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
	if (epsilonEqual(lhs->t, rhs->t))
		return lhs->s < rhs->s;
	return lhs->t < rhs->t;
};

class Intersections {
public:
	Intersections() {};
	Intersections(const std::set<Intersection*, decltype(cmp)>& i) : intersections(i) {

	}

	Intersection* hit()const;
	std::set<Intersection*, decltype(cmp)> intersections;
};

