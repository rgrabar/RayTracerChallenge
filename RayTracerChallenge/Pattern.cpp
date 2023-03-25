#include "Pattern.h"
#include "Shape.h"



// TODO: remove this
#include "Sphere.h"
#include "Plane.h"
#include "Cylinder.h"

Color StripePattern::patternColorAt(const Tuple& point, const Shape* shape)const {

	if (isNested) {
		if ((int)floor(point.x) % 2 == 0)
			return patternA->patternColorAt(point);
		else
			return patternB->patternColorAt(point);
	}

	//TODO: why can't i do just (int), negative numbers?
	if ((int)floor(point.x) % 2 == 0)
		return a;
	return b;
}

Color GradientPattern::patternColorAt(const Tuple& point, const Shape* shape)const {
	auto distance = b - a;
	auto fraction = point.x - floor(point.x);

	return a + distance * fraction;
}

Color CheckerPattern::patternColorAt(const Tuple& point, const Shape* shape)const {
	if (isNested) {
		if (((int)(floor(point.x) + floor(point.y) + floor(point.z))) % 2 == 0)
			return patternA->patternColorAt(point);
		else
			return patternB->patternColorAt(point);
	}

	if (((int)(floor(point.x) + floor(point.y) + floor(point.z))) % 2 == 0)
		return a;
	else
		return b;
}

Color RingPattern::patternColorAt(const Tuple& point, const Shape* shape)const {
	if (isNested) {
		if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0)
			return patternA->patternColorAt(point);
		else
			return patternB->patternColorAt(point);
	}

	if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0)
		return a;
	else
		return b;
}

Color RadialGradientPattern::patternColorAt(const Tuple& point, const Shape* shape)const {
	if (!type) {

		if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0) {

			auto m = point.magnitude();

			auto distance = b - a;
			auto fraction = m - floor(m);
			return a + distance * fraction;
		}
		else {

			auto m = point.magnitude();

			auto distance = b - a;
			auto fraction = m - floor(m);

			return a + distance * fraction;
		}

	}
	// additional radial patern  
	if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0) {
		auto distance = b - a;
		auto fraction = point.x - floor(point.x);
		return a + distance * fraction;
	}
	else {
		auto distance = a - b;
		auto fraction = point.x - floor(point.x);

		return b + distance * fraction;
	}
}

Color BlendedPattern::patternColorAt(const Tuple & point, const Shape* shape) const {

	// TODO: this works but is it even correct? the transform part shouldn't it be transformed?

	auto patternPointA = (a->transform) * point;
	auto patternPointB = (b->transform) * point;

	Color aCol = a->patternColorAt(patternPointA);
	Color bCol = b->patternColorAt(patternPointB);

	return (aCol + bCol) / 2.f;
}

Color UVCheckers::patternColorAt(const Tuple& point, const Shape* shape)const  {
	double a, b;
	// TODO: check if null or somehting
	shape->UVmap(point, &a, &b);
	return uvPatternAt(a, b);
}

Color AlignCheck::patternColorAt(const Tuple& point, const Shape* shape)const {
	double a, b;
	// TODO: check if null or somehting
	shape->UVmap(point, &a, &b);
	return uvPatternAt(a, b);
}

Color TestPatern::patternColorAt(const Tuple& object_point, const Shape* shape)const {
	return Color(object_point.x, object_point.y, object_point.z);
}