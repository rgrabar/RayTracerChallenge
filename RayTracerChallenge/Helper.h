#pragma once
#include <cmath>

// TODO: better way to handle epsilon?

#ifdef DEBUG
	const double EPSILON = 0.00001;
	inline bool epsilonEqual(double a, double b) { return std::abs(a - b) < EPSILON; }
#else
	const double EPSILON = 0.00000000001;
	inline bool epsilonEqual(double a, double b) { return std::abs(a - b) < EPSILON; }
#endif

