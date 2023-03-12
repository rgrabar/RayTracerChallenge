#include "GradientPattern.h"
#include <math.h>

Color GradientPattern::patternColorAt(const Tuple& point)const {
	auto distance = b - a;
	auto fraction = point.x - floor(point.x);

	return a + distance * fraction;
}