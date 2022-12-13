#include "Intersection.h"

Intersection::Intersection(float _t, const void* _s) : t(_t), s(_s) {}

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
