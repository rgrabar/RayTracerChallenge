#pragma once

#include "Color.h"
#include "Tuple.h"
#include "Shape.h"
#include <vector>

// TODO: this is here because of intensityAt can i move it somewhere?
struct World;

struct Light {

	virtual bool operator==(const Light& other)const = 0;

	Color intensity;
	Tuple position;
	std::vector<Tuple> lightSamples;
	int samples = 1;

	Light(const Color& _intensity, const Tuple& _position, const int _samples) : intensity(_intensity), position(_position), samples(_samples) {}
	// TODO: remove duplicated code for lighting
	Color lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const double intensityAt);
	virtual double intensityAt(const Tuple& point, const World& world) = 0;
};


struct PointLight : public Light {

	PointLight(const Color& _intensity, const Tuple& _position);

	bool operator==(const Light& other)const;
	double intensityAt(const Tuple& point, const World& world);
};

struct SpotLight : public Light {

	SpotLight(const Color& _intensity, const Tuple& _position, const Tuple& _direction, double _angle, int _samples, double _radius);
	// TODO: change compare operator
	bool operator==(const Light& other)const;

	double intensityAt(const Tuple& point, const World& world);
	Tuple pointOnLight();

	Tuple direction;
	double angle;
	double fadeIntensity = 1;
	double radius;
	bool isSoft = 1;

};

struct AreaLight : public Light {

	AreaLight(const Tuple& _corner, const Tuple& _fullUvec, int _uSteps, const Tuple& _fullVvec, int _vSteps, Color _intensity);
	// TODO: change compare operator
	bool operator==(const Light& other)const;

	double intensityAt(const Tuple& point, const World& world);

	Tuple pointOnLight(int u, int v);

	Tuple corner;
	Tuple uVec;
	Tuple vVec;
	int uSteps;
	int vSteps;
	bool jitter = 1;
	bool isSoft = 1;
};

// Test light for arealight jitter tests
struct TestLight : public Light {

	TestLight(const Tuple& _corner, const Tuple& _fullUvec, int _uSteps, const Tuple& _fullVvec, int _vSteps, Color _intensity);
	// TODO: change compare operator
	bool operator==(const Light& other)const;

	double intensityAt(const Tuple& point, const World& world);

	Tuple pointOnLight(int u, int v);

	double next();

	Tuple corner;
	Tuple uVec;
	Tuple vVec;
	int uSteps;
	int vSteps;
	bool jitter = 0;
	int cur = 0;

	std::vector<double>* seq;

};


