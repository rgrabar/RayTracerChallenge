#pragma once
#include "Color.h"
#include "Light.h"
#include "Tuple.h"

struct Material {

	Material():color(Color(1, 1, 1)) {}

	Color color;
	double ambient = 0.1;
	double diffuse = 0.9;
	double specular = 0.9;
	double shininess = 200;

	Color lighting(const Light& light, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow)const;
};

bool operator==(const Material& lhs, const Material& rhs);