#include "Normal.h"
#include <iostream>

Tuple normal_at(const Shape& s, const Tuple& worldPoint) {
	return s.normalAt(worldPoint);
}

Tuple reflect(const Tuple& in, const Tuple& normal) {
	return in - normal * 2 * in.dotProduct(normal);
}