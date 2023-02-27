#pragma once

#include "Color.h"
#include "Tuple.h"
#include "Shape.h"

// TODO: this is here because of intensityAt can i move it somewhere?
class World;

class Light {
public:

	virtual bool operator==(const Light& other)const = 0;

	Color intesity;
	Tuple position;
	Light(const Color& _intensity, const Tuple& _position) : intesity(_intensity), position(_position) {}

	virtual Color lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow) = 0;
	virtual double intensityAt(const Tuple& point, const World& world) = 0;
};


class PointLight : public Light {

public:

	PointLight(const Color& _intensity, const Tuple& _position);

	bool operator==(const Light& other)const;

	Color lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow);
	double intensityAt(const Tuple& point, const World& world);
};

class SpotLight : public Light {

public:


	SpotLight(const Color& _intensity, const Tuple& _position, const Tuple& _direction, double _angle);

	bool operator==(const Light& other)const;

	Color lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow);
	double intensityAt(const Tuple& point, const World& world);

	Tuple direction;
	double angle;
	double fadeIntensity = 1;

};

