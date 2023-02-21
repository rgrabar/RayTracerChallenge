#include "Light.h"

Light::Light(const Color& _intensity, const Tuple& _position) : intesity(_intensity), position(_position) {}

bool Light::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Color Light::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow) {

	Color newColor = material.color;

	if (material.pattern != nullptr)
		newColor = object->stripeAtObject(point);

	auto effectiveColor = newColor * intesity;
	auto lightv = (position - point).normalize();
	auto ambientColor = effectiveColor * object->material.ambient;
	auto lightDotNormal = lightv.dotProduct(normalv);

	Color diffuseColor(0, 0, 0);
	Color specularColor(0, 0, 0);

	if (lightDotNormal < 0) {
		diffuseColor = Color(0, 0, 0);
		specularColor = Color(0, 0, 0);
	}
	else {
		diffuseColor = effectiveColor * object->material.diffuse * lightDotNormal;
		auto reflectv = -lightv.reflect(normalv);
		auto reflectDotEye = reflectv.dotProduct(eyev);

		if (reflectDotEye <= 0)
			specularColor = Color(0, 0, 0);
		else {
			auto factor = pow(reflectDotEye, object->material.shininess);
			specularColor = intesity * object->material.specular * factor;
		}
	}

	auto test = ambientColor + diffuseColor + specularColor;

	if (inShadow)
		return ambientColor;
	else
		return ambientColor + diffuseColor + specularColor;
}