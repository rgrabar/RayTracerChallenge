#include "RadialGradientPattern.h"
#include <iostream>

Color RadialGradientPattern::patternColorAt(const Tuple& point)const {
	if (!type) {

		if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0) {

			auto m = point.magnitude();

			auto distance = b - a;
			auto fraction = m - floor(m);
			return a + distance * fraction;
		}
		else {

			auto m = point.magnitude();

			auto distance = b - a;
			auto fraction = m - floor(m);

			return a + distance * fraction;
		}

	}
	// additional radial patern  
	if ((int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0) {
		auto distance = b - a;
		auto fraction = point.x - floor(point.x);
		return a + distance * fraction;
	}
	else {
		auto distance = a - b;
		auto fraction = point.x - floor(point.x);

		return b + distance * fraction;
	}
	
}