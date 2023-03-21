#pragma once
#include "Color.h"
#include "Tuple.h"
#include "Matrix.h"
#include <math.h>

class Pattern {
public:
	Color a;
	Color b;
	Matrix transform = identityMatrix(4);
	Pattern() : a(Color(1, 1, 1)), b(Color(0, 0, 0)) {}
	Pattern(const Color& _a, const Color& _b) : a(_a), b(_b) {}

	virtual Color patternColorAt(const Tuple& point)const = 0;
};

class StripePattern :public Pattern {
public:
	Pattern* patternA = nullptr;
	Pattern* patternB = nullptr;
	bool isNested = false;

	StripePattern() {}
	StripePattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	StripePattern(Pattern* _a, Pattern* _b) : patternA(_a), patternB(_b), isNested(true) {}

	Color patternColorAt(const Tuple& point)const override {

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
};

class GradientPattern : public Pattern {
public:
	GradientPattern() {}
	GradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}


	Color patternColorAt(const Tuple& point)const override {
		auto distance = b - a;
		auto fraction = point.x - floor(point.x);

		return a + distance * fraction;
	}
};

class CheckerPattern : public Pattern {
public:
	// use for nested patterns e.g. have a checkered pattern with different nested stripe patterns
	Pattern* patternA = nullptr;
	Pattern* patternB = nullptr;
	bool isNested = false;

	CheckerPattern() {}
	CheckerPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	CheckerPattern(Pattern* _a, Pattern* _b) : patternA(_a), patternB(_b), isNested(true) {}

	Color patternColorAt(const Tuple& point)const override {
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
};

class RingPattern : public Pattern {
public:
	Pattern* patternA = nullptr;
	Pattern* patternB = nullptr;
	bool isNested = false;

	RingPattern() {}
	RingPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	RingPattern(Pattern* _a, Pattern* _b) : patternA(_a), patternB(_b), isNested(true) {}

	Color patternColorAt(const Tuple& point)const override {
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
};

class RadialGradientPattern : public Pattern {
public:

	int type = 0;

	RadialGradientPattern() {}
	RadialGradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	RadialGradientPattern(const Color& _a, const Color& _b, int _type) : Pattern(_a, _b), type(_type) {}

	Color patternColorAt(const Tuple& point)const override {
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
};

class BlendedPattern :public Pattern {
public:
	BlendedPattern() {}
	BlendedPattern(Pattern* _a, Pattern* _b) : a(_a), b(_b) {}

	Color patternColorAt(const Tuple& point) const override {

		// TODO: this works but is it even correct? the transform part shouldn't it be transformed?

		auto patternPointA = (a->transform) * point;
		auto patternPointB = (b->transform) * point;

		Color aCol = a->patternColorAt(patternPointA);
		Color bCol = b->patternColorAt(patternPointB);

		return (aCol + bCol) / 2.f;
	}
	Pattern* a = nullptr;
	Pattern* b = nullptr;
};

class TestPatern :public Pattern{
public:
	 Color patternColorAt(const Tuple& object_point)const override {
		return Color(object_point.x, object_point.y, object_point.z);
	}
};