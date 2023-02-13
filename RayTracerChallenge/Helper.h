#pragma once
#include <cmath>
const double EPSILON = 0.00000000001;

inline bool epsilonEqual(double a, double b) { return std::abs(a - b) < EPSILON; };