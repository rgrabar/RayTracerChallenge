#include "Light.h"

PointLight::PointLight(const Color& _intensity, const Tuple& _position) : Light(_intensity, _position) {}

bool PointLight::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Color PointLight::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow) {

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


SpotLight::SpotLight(const Color& _intensity, const Tuple& _position, const Tuple& _direction, double _angle) : Light(_intensity, _position), direction((_direction - _position).normalize()), angle(_angle){}

bool SpotLight::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Color SpotLight::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow) {
	
	Tuple light_dir = (point - position).normalize();

	double cos_theta = light_dir.dotProduct(direction);
	
	//std::cout << cos_theta << " " << std::cos(angle) << "\n";

	if (cos_theta < std::cos(angle)) {
		return Color (0, 0, 0);
	}


	double diff = std::max(0.0, normalv.dotProduct(light_dir)) * material.diffuse;
	Tuple reflect_dir = light_dir - normalv * 2 * light_dir.dotProduct(normalv);
	double spec = std::pow(std::max(0.0, reflect_dir.dotProduct(eyev)), material.shininess) * material.specular;
	Color light_color = material.color * intesity;
	Color final_color = material.color * diff + light_color * spec;

	
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