#include "Light.h"

// TODO: this is here because of intensityAt can i move it somewhere?
#include "World.h"

PointLight::PointLight(const Color& _intensity, const Tuple& _position) : Light(_intensity, _position) {}

bool PointLight::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Color PointLight::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const double intensityAt) {

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


	return ambientColor + (diffuseColor + specularColor) * (intensityAt);
}

double PointLight::intensityAt(const Tuple& point, const World& world) {

	if(world.isShadowed(point, position))
		return 0.0;
	return 1.0;
}


SpotLight::SpotLight(const Color& _intensity, const Tuple& _position, const Tuple& _direction, double _angle) : Light(_intensity, _position), direction((_direction - _position).normalize()), angle(_angle){}

bool SpotLight::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Color SpotLight::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const double intensityAt) {
	
	Tuple light_dir = (point - position).normalize();
	double cos_theta = light_dir.dotProduct(direction);

	if (cos_theta < std::cos(angle)) {
		return Color (0, 0, 0);
	}

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

	if (intensityAt)
		return ambientColor;
	else
		return (ambientColor + diffuseColor + specularColor) * (1 - std::pow((std::acos(cos_theta) / angle), fadeIntensity));
}

double SpotLight::intensityAt(const Tuple& point, const World& world) {
	// TODO: move * (1 - std::pow((std::acos(cos_theta) / angle), fadeIntensity) here
	return 0;
}


AreaLight::AreaLight(const Tuple& _corner, const Tuple& _fullUvec, int _uSteps, const Tuple& _fullVvec, int _vSteps, Color _intensity) :
	Light(_intensity, _corner + (_fullUvec + _fullVvec) / 2.0f),
	corner(_corner),
	uVec(_fullUvec / _uSteps),
	vVec(_fullVvec / _vSteps),
	samples(_uSteps * _vSteps),
	uSteps(_uSteps),
	vSteps(_vSteps)
{
	for (int v = 0; v < vSteps; ++v) {
		for (int u = 0; u < uSteps; ++u) {
			lightSamples.emplace_back(pointOnLight(u, v));
		}
	}

}



Color AreaLight::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const double intensityAt) {
	Color newColor = material.color;

	if (material.pattern != nullptr)
		newColor = object->stripeAtObject(point);

	auto effectiveColor = newColor * intesity;
	auto ambientColor = effectiveColor * object->material.ambient;

	Color sum = Color(0, 0, 0);

	for (auto sample : lightSamples) {

		Color diffuseColor(0, 0, 0);
		Color specularColor(0, 0, 0);

		auto lightv = (sample - point).normalize();
		auto lightDotNormal = lightv.dotProduct(normalv);
		
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

		sum = sum + diffuseColor;
		sum = sum + specularColor;
	}
	//auto test = ambientColor + diffuseColor + specularColor;

	return ambientColor + (sum / samples) * (intensityAt);
}
double AreaLight::intensityAt(const Tuple& point, const World& world) {
	auto total = 0.0;

	for (int v = 0; v < vSteps; ++v) {
		for (int u = 0; u < uSteps; ++u) {
			auto lightPosition = pointOnLight(u, v);

			if (!world.isShadowed(lightPosition, point)) {
				total = total + 1.0;
			}
		}
	}
	return total / samples;
}

bool AreaLight::operator==(const Light& other)const {
	return other.intesity == intesity && other.position == position;
}

Tuple AreaLight::pointOnLight(int u, int v) {
	return corner +
		uVec * (u + random_double()) +
		vVec * (v + random_double());
}