#include "CheckerPattern.h"
#include <math.h>

Color CheckerPattern::patternColorAt(const Tuple& point)const {
	
	if (((int)(floor(point.x) + floor(point.y) + floor(point.z))) % 2 == 0)
		return a;
	else
		return b;
}