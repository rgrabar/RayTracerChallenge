#include "Light.h"

// TODO: this is here because of intensityAt can i move it somewhere?
#include "World.h"

Color Light::lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const double intensityAt) {
	Color newColor = material.color;

	if (material.pattern != nullptr)
		// TODO: rename stripeatobject to something that makes more sense
		newColor = object->stripeAtObject(point);

	auto effectiveColor = newColor * intensity;
	auto ambientColor = effectiveColor * object->material.ambient;

	if (epsilonEqual(intensityAt, 0.0))
		return ambientColor;

	Color sum = Color(0, 0, 0);

	for (const Tuple& sample : lightSamples) {

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
				specularColor = intensity * object->material.specular * factor;
			}
		}

		sum += diffuseColor + specularColor;
	}
	//auto test = ambientColor + diffuseColor + specularColor;

	return ambientColor + (sum / samples) * (intensityAt);
}

PointLight::PointLight(const Color& _intensity, const Tuple& _position) : Light(_intensity, _position, 1) {
	lightSamples.emplace_back(position);
}

bool PointLight::operator==(const Light& other)const {
	return other.intensity == intensity && other.position == position;
}

double PointLight::intensityAt(const Tuple& point, const World& world) {

	if(world.isShadowed(point, position))
		return 0.0;
	return 1.0;
}


SpotLight::SpotLight(const Color& _intensity, const Tuple& _position, const Tuple& _direction, double _angle, int _samples, double _radius) : 
	Light(_intensity, _position, _samples), direction((_direction - _position).normalize()), angle(_angle), radius(_radius)
{
	for (int v = 0; v < samples; ++v) {
		lightSamples.emplace_back(pointOnLight());
	}
}

bool SpotLight::operator==(const Light& other)const {
	return other.intensity == intensity && other.position == position;
}

double SpotLight::intensityAt(const Tuple& point, const World& world) {
	Tuple light_dir = (point - position).normalize();
	double cos_theta = light_dir.dotProduct(direction);

	if (cos_theta < std::cos(angle)) {
		return 0.f;
	}

	if (!isSoft) {
		if (world.isShadowed(point, position))
			return 0.0;
		return 1.0 * (1 - std::pow((std::acos(cos_theta) / angle), fadeIntensity));
	}

	auto total = 0.0;

	for (int v = 0; v < samples; ++v) {
			
		auto lightPosition = pointOnLight();
			if (!world.isShadowed(lightPosition, point)) {
				total = total + 1.0;
			}
	}
	return total / samples * (1 - std::pow((std::acos(cos_theta) / angle), fadeIntensity));
}

Tuple SpotLight::pointOnLight() {

	// https://mathworld.wolfram.com/DiskPointPicking.html
	// random points in a uniform circle r E [0, 1] and phi E (0, 2*pi)
	
	auto r = random_double();
	auto phi = random_double() * 2 * M_PI;

	auto x = sqrt(r) * cos(phi);
	auto y = sqrt(r) * sin(phi);

	// https://stackoverflow.com/questions/41275311/a-good-way-to-find-a-vector-perpendicular-to-another-vector
	// random non collinear vector
	Tuple randomDir = (Tuple::vector(random_double(), random_double(), random_double())).normalize();

	// 2 vectors both ortogonal to the normal and ortogonal to each other to define the circle
	Tuple ortogonalToDirection = randomDir.crossProduct(direction).normalize();
	Tuple ortogonalToBoth = (ortogonalToDirection.crossProduct(direction)).normalize();

	auto randomPoint = ortogonalToDirection * x + ortogonalToBoth * y;

	return position + randomPoint * radius;

}

AreaLight::AreaLight(const Tuple& _corner, const Tuple& _fullUvec, int _uSteps, const Tuple& _fullVvec, int _vSteps, Color _intensity) :
	Light(_intensity, _corner + (_fullUvec + _fullVvec) / 2 , _uSteps * _vSteps),
	corner(_corner),
	uVec(_fullUvec / _uSteps),
	vVec(_fullVvec / _vSteps),
	uSteps(_uSteps),
	vSteps(_vSteps)
{
	for (int v = 0; v < vSteps; ++v) {
		for (int u = 0; u < uSteps; ++u) {
			lightSamples.emplace_back(pointOnLight(u, v));
		}
	}
}

double AreaLight::intensityAt(const Tuple& point, const World& world) {
	
	if (!isSoft) {
		if (world.isShadowed(point, position))
			return 0.0;
		return 1.0;
	}
	
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
	return other.intensity == intensity && other.position == position;
}

Tuple AreaLight::pointOnLight(int u, int v) {
	if (jitter) {
		return corner +
			uVec * (u + random_double()) +
			vVec * (v + random_double());
	}

	return corner +
		uVec * (u + 0.5) +
		vVec * (v + 0.5);
}

TestLight::TestLight(const Tuple& _corner, const Tuple& _fullUvec, int _uSteps, const Tuple& _fullVvec, int _vSteps, Color _intensity) :
	Light(_intensity, _corner + (_fullUvec + _fullVvec) / 2.0f, _uSteps * _vSteps),
	corner(_corner),
	uVec(_fullUvec / _uSteps),
	vVec(_fullVvec / _vSteps),
	uSteps(_uSteps),
	vSteps(_vSteps),
	jitter(false)
{
	// TODO: why do some tests pass with this and some don't?
	for (int v = 0; v < vSteps; ++v) {
		for (int u = 0; u < uSteps; ++u) {
			lightSamples.emplace_back(pointOnLight(u, v));
		}
	}
}

double TestLight::intensityAt(const Tuple& point, const World& world) {
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

bool TestLight::operator==(const Light& other)const {
	return other.intensity == intensity && other.position == position;
}

Tuple TestLight::pointOnLight(int u, int v) {
	if (jitter) {
		// order is important
		auto res = corner;
		res += uVec * (u + next());
		res += vVec * (v + next());
		return res;
	}

	return corner +
		uVec * (u + 0.5) +
		vVec * (v + 0.5);
}

double TestLight::next() {
	return seq->operator[](cur++ % seq->size());
}