#include "Sphere.h"

bool Sphere::operator==(const Sphere& o) const {
	//TODO: CHECK TRANSFORM
	return o.origin == origin;
}