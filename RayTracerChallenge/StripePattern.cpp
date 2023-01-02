#include "StripePattern.h"

Color StripePattern::patternColorAt(const Tuple& point) {

	//TODO: why can't i do just (int), negative numbers?
	if ((int)floor(point.x) % 2 == 0)
		return a;
	return b;
}