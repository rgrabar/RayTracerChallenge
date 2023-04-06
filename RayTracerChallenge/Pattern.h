#pragma once
#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"
#include "Matrix.h"

#include <cassert>
#include <iostream>
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

class AlignCheck :public Pattern {
public:
	AlignCheck(Color _main, Color _ul, Color _ur, Color _bl, Color _br) : main(_main), ul(_ul), ur(_ur), bl(_bl), br(_br) {}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;

	Color uvPatternAt(double u, double v) const;

	Color main;
	Color ul;
	Color ur;
	Color bl;
	Color br;
};

class CubeMap :public Pattern {
public:
	// TODO: is there a way to guarantee order?
	CubeMap(Pattern* _front, Pattern* _back, Pattern* _left, Pattern* _right, Pattern* _up, Pattern* _down) : faces{ _front, _back, _left, _right, _up, _down } {

	}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;

	Color uvPatternAt(double u, double v) const;

	Pattern* faces[6];
};

class UVImagePattern :public Pattern {
public:
	UVImagePattern(Canvas* _canvas) : canvas(_canvas) {

	}

	Color patternColorAt(const Tuple& point, const Shape* shape = nullptr)const override;

	Color uvPatternAt(double u, double v) const;
	Canvas* canvas;
};



class TestPatern :public Pattern{
public:
	Color patternColorAt(const Tuple& object_point, const Shape* shape = nullptr)const override;
};