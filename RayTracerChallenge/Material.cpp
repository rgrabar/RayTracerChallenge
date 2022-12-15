#include "Material.h"
#include "Normal.h"
#include <iostream>

Color Material::lighting(const Light& light, const Tuple& point, const Tuple& eyev, const Tuple& normalv)const {
	auto effectiveColor = color * light.intesity;
	auto lightv = (light.position - point).normalize();
	auto ambientColor = effectiveColor * ambient;
	auto lightDotNormal = lightv.dotProduct(normalv);

	Color diffuseColor(0, 0, 0);
	Color specularColor(0, 0, 0);

	if (lightDotNormal < 0) {
		diffuseColor = Color(0, 0, 0);
		specularColor = Color(0, 0, 0);
	} else {
		diffuseColor = effectiveColor * diffuse * lightDotNormal;
		auto reflectv = reflect(-lightv, normalv);
		auto reflectDotEye = reflectv.dotProduct(eyev);

		if (reflectDotEye <= 0)
			specularColor = Color(0, 0, 0);
		else {
			auto factor = pow(reflectDotEye, shininess);
			specularColor = light.intesity * specular * factor;
		}
	}
	
	auto test = ambientColor + diffuseColor + specularColor;

	return ambientColor + diffuseColor + specularColor;
}

bool operator==(const Material& lhs, const Material& rhs) {
 return lhs.color == rhs.color && lhs.ambient == rhs.ambient
	 && lhs.diffuse == rhs.diffuse && lhs.specular == rhs.specular
	 && lhs.shininess == rhs.shininess;
}