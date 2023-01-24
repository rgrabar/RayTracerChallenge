#include "Normal.h"
#include <iostream>
#include "Pattern.h"

Tuple reflect(const Tuple& in, const Tuple& normal) {
	return in - normal * 2 * in.dotProduct(normal);
}

Color lighting(Shape* object, const Light& light, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow){

	Color newColor = object->material.color;

	if (object->material.pattern != nullptr)
		newColor = object->stripeAtObject(point);

	auto effectiveColor = newColor * light.intesity;
	auto lightv = (light.position - point).normalize();
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
		auto reflectv = reflect(-lightv, normalv);
		auto reflectDotEye = reflectv.dotProduct(eyev);

		if (reflectDotEye <= 0)
			specularColor = Color(0, 0, 0);
		else {
			auto factor = pow(reflectDotEye, object->material.shininess);
			specularColor = light.intesity * object->material.specular * factor;
		}
	}

	auto test = ambientColor + diffuseColor + specularColor;

	if (inShadow)
		return ambientColor;
	else
		return ambientColor + diffuseColor + specularColor;
}