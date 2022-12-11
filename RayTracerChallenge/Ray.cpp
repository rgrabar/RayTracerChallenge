#include "Ray.h"

Tuple Ray::position(float t) const{
	return origin + direction * t;
}

Ray Ray::transform(const Matrix& m) {

	return Ray(m * origin, m * direction);
}