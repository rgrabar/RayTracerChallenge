#pragma once
#include "Color.h"
#include "Light.h"
#include "Tuple.h"

struct Material {

	Material():color(Color(1, 1, 1)) {}

	Color color;
	float ambient = 0.1;
	float diffuse = 0.9;
	float specular = 0.9;
	float shininess = 200;

	Color lighting(Light light, Tuple point, Tuple eyev, Tuple normalv);
};

bool operator==(const Material lhs, const Material rhs);