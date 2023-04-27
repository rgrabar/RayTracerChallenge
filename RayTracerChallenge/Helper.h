#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _USE_MATH_DEFINES
#endif

#include <cmath>

// TODO: better way to handle epsilon?

#ifdef FOR_TEST
	const double EPSILON = 0.00001;
	inline bool epsilonEqual(double a, double b) { return std::abs(a - b) < EPSILON; }
#else
	const double EPSILON = 0.00000000001;
	inline bool epsilonEqual(double a, double b) { return std::abs(a - b) < EPSILON; }
#endif //FOR_TEST

inline double random_double() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0);
}
