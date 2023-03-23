#pragma once
#include "Color.h"
#include "Tuple.h"
#include "Matrix.h"
#include <math.h>

class Shape;

class Pattern {
public:
	Color a;
	Color b;
	Matrix transform = identityMatrix(4);
	Pattern() : a(Color(1, 1, 1)), b(Color(0, 0, 0)) {}
	Pattern(const Color& _a, const Color& _b) : a(_a), b(_b) {}

	virtual Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const = 0;
};

class StripePattern :public Pattern {
public:
	Pattern* patternA = nullptr;
	Pattern* patternB = nullptr;
	bool isNested = false;

	StripePattern() {}
	StripePattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	StripePattern(Pattern* _a, Pattern* _b) : patternA(_a), patternB(_b), isNested(true) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;
};

class GradientPattern : public Pattern {
public:
	GradientPattern() {}
	GradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}


	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;
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

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;
};

class RingPattern : public Pattern {
public:
	Pattern* patternA = nullptr;
	Pattern* patternB = nullptr;
	bool isNested = false;

	RingPattern() {}
	RingPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	RingPattern(Pattern* _a, Pattern* _b) : patternA(_a), patternB(_b), isNested(true) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;
};

class RadialGradientPattern : public Pattern {
public:

	int type = 0;

	RadialGradientPattern() {}
	RadialGradientPattern(const Color& _a, const Color& _b) : Pattern(_a, _b) {}
	RadialGradientPattern(const Color& _a, const Color& _b, int _type) : Pattern(_a, _b), type(_type) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;
};

class BlendedPattern :public Pattern {
public:
	BlendedPattern() {}
	BlendedPattern(Pattern* _a, Pattern* _b) : a(_a), b(_b) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr) const override;
	Pattern* a = nullptr;
	Pattern* b = nullptr;
};

class UVCheckers :public Pattern {
public:
	UVCheckers() : a(1, 1, 1), b(0, 0, 0) {}
	UVCheckers(int _u, int _v, Color _a, Color _b) : widht(_u), height(_v), a(_a), b(_b) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;

	Color uvPatternAt(double u, double v) const  {
		int u2 = floor(u * widht);
		int v2 = floor(v * height);

		if ((u2 + v2) % 2 == 0) {
			
			return a;
		}
		else {
			return b;
		}
	}

	int widht, height;
	Color a;
	Color b;
};


class TestPatern :public Pattern{
public:
	Color patternColorAt(const Tuple& object_point, const Shape* shape = nullptr)const override;
};