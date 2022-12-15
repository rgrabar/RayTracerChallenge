#include "Ray.h"

Tuple Ray::position(float t)const{
	return origin + direction * t;
}

Ray Ray::transform(const Matrix& m)const {

	return Ray(m * origin, m * direction);
}