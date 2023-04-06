#include "Pattern.h"
#include "Shape.h"

#include "Cube.h"

Color StripePattern::patternColorAt(const Tuple& point, const Shape* shape)const {

	if (isNested) {
		if ((int)floor(point.x) % 2 == 0)
			return patternA->patternColorAt(point);
		else
			return patternB->patternColorAt(point);
	}

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

Color AlignCheck::uvPatternAt(double u, double v) const {
	if (v > 0.8) {
		if (u < 0.2)
			return ul;
		if (u > 0.8)
			return ur;
	}
	else if (v < 0.2) {
		if (u < 0.2)
			return bl;
		if (u > 0.8)
			return br;
	}
	return main;
}

Color CubeMap::patternColorAt(const Tuple& point, const Shape* shape)const {
	double a, b;
	// TODO: check if null or somehting
	shape->UVmap(point, &a, &b);
	int face = Cube::faceFromPoint(point);
	return faces[face]->patternColorAt(point, shape);
}

Color CubeMap::uvPatternAt(double u, double v) const {
	std::cout << "This should not be called. The pattern type for face should be called!";
	assert(0);
}

Color UVImagePattern::patternColorAt(const Tuple& point, const Shape* shape)const {
	double a, b;
	// TODO: check if null or somehting
	if (shape == nullptr)
		return Color(0, 0, 0);
	shape->UVmap(point, &a, &b);
	return uvPatternAt(a, b);
}

Color UVImagePattern::uvPatternAt(double u, double v) const {
	v = 1 - v;
	auto x = u * (canvas->w - 1);
	auto y = v * (canvas->h - 1);

	return canvas->canvas[(int)round(y) * canvas->w + (int)round(x)];
}

Color TestPatern::patternColorAt(const Tuple& object_point, const Shape* shape)const {
	return Color(object_point.x, object_point.y, object_point.z);
}