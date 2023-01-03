#include "RingPattern.h"
#include <math.h>

Color RingPattern::patternColorAt(const Tuple& point){
	if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0)
		return a;
	else
		return b;
}