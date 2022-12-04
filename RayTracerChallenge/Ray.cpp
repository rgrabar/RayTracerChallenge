#include "Ray.h"

Tuple Ray::position(float t) const{
	return origin + direction * t;
}

Ray Ray::transform(Matrix m) {

	return Ray(m * origin, m * direction);
}