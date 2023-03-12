#pragma once
#include "Color.h"
#include "Pattern.h"

struct Material {

	Material():color(Color(1, 1, 1)) {}

	Color color;
	double ambient = 0.1;
	double diffuse = 0.9;
	double specular = 0.9;
	double shininess = 200;
	double reflective = 0.0;
	double transparency = 0.0;
	double refractiveIndex = 1.0;
	Pattern* pattern = nullptr;

};

bool operator==(const Material& lhs, const Material& rhs);