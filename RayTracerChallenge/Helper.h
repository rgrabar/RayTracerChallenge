#pragma once
#include <cmath>
const float EPSILON = 0.00001 * 3;

inline bool epsilonEqual(float a, float b) { return fabs(a - b) < EPSILON; };