#include "Normal.h"
#include <iostream>
#include "Pattern.h"

Tuple normal_at(const Shape& s, const Tuple& worldPoint) {

	auto objectPoint = s.transform.inverse() * worldPoint;
	auto objectNormal = s.normalAt(objectPoint);
	auto worldNormal = s.transform.inverse().transpose() * objectNormal;
	worldNormal.w = 0;

	return (worldNormal.normalize());
}

Tuple reflect(const Tuple& in, const Tuple& normal) {
	return in - normal * 2 * in.dotProduct(normal);
}

std::vector<Intersection> intersect(const Shape* object, const Ray& ray) {

	// put ray in object space needed before intersect function
	auto rayCalc = ray.transform(object->transform.inverse());
	return object->intersect(rayCalc);;
}

Color stripeAtObject(const Shape* object, const Tuple& worldPoint) {
	auto objectPoint = object->transform.inverse() * worldPoint;
	auto patternPoint = object->material.pattern->transform.inverse() * objectPoint;

	return object->material.pattern->stripeAt(patternPoint);
}

Color lighting(const Shape* object, const Light& light, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow){

	Color newColor = object->material.color;

	if (object->material.pattern != nullptr)
		newColor = stripeAtObject(object, point);

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