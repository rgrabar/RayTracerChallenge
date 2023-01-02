#include "GradientPattern.h"
#include <math.h>
#include <iostream>

Color GradientPattern::patternColorAt(const Tuple& point) {
	auto distance = b - a;
	auto fraction = point.x - floor(point.x);

	return a + distance * fraction;
}