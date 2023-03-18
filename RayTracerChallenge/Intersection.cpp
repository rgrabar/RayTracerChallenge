#include "Intersection.h"
#include "Shape.h"

Intersection::Intersection(double _t, const void* _s) : t(_t), s(_s) {}

Intersection::Intersection(double _t, const void* _s, double _u, double _v) : t(_t), s(_s), u(_u), v(_v) {}

Intersection* Intersections::hit(const bool optOutShadow)const {

	for (auto& x : intersections) {
		if (x->t < 0)
			continue;

		else if (((Shape*)x->s)->optOutShadow && optOutShadow)
			continue;
		else
			return x;
	}

	return nullptr;
}
