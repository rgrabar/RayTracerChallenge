#include "Pattern.h"
#include <iostream>
#include <math.h>

Pattern::Pattern() : a(Color(1, 1, 1)), b(Color(0, 0, 0)) {}

Pattern::Pattern(const Color& _a, const Color& _b) : a(_a), b(_b) {}

Color Pattern::stripeAt(const Tuple& point)const {

	if ((int)floor(point.x) % 2 == 0)
		return a;
	return b;
}