#include "Intersection.h"

Intersection::Intersection(double _t, Shape* _s) : t(_t), s(_s) {}


Intersection* Intersections::hit() {

	for (auto& x : intersections) {
		if (x->t < 0)
			continue;
		else
			return x;
	}

	return nullptr;
}
