#include "Light.h"

Light::Light(const Color& _intensity, const Tuple& _position) : intesity(_intensity), position(_position) {}

bool Light::operator==(const Light& other) const {
	return other.intesity == intesity && other.position == position;
}
