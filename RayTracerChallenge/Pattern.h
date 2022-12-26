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