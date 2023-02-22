#pragma once
#include "Color.h"
#include "Tuple.h"
#include "Matrix.h"

class Pattern {
public:
	Color a;
	Color b;
	Matrix transform = identityMatrix(4);
	Pattern();
	Pattern(const Color& _a, const Color& _b);

	virtual Color patternColorAt(const Tuple& point)const = 0;
};

class TestPatern :public Pattern{
public:
	 Color patternColorAt(const Tuple& object_point)const override {
		return Color(object_point.x, object_point.y, object_point.z);
	}
};