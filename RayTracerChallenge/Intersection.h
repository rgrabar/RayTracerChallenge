#pragma once

#include <set>
#include "Helper.h"

class Intersection {
public:

	// di ga je hit
	double t;
	const void* s;
	double u;
	double v;

	Intersection(double _t, const void* _s);

	Intersection(double _t, const void* _s, double _u, double _v);

};

struct cmp {
    bool operator()(const Intersection* lhs, const Intersection* rhs) const {
        return lhs->t <= rhs->t;
    }
};

class Intersections {
public:
    Intersections() {};
    Intersections(const std::multiset<Intersection*, cmp>& i) : intersections(i) {

    }

    Intersection* hit()const;
    std::multiset<Intersection*, cmp> intersections;
};