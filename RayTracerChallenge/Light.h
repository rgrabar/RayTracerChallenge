#pragma once

#include "Color.h"
#include "Tuple.h"
#include "Shape.h"

class Light {
public:
	
	Light(const Color& _intensity, const Tuple& _position);

	bool operator==(const Light& other)const;

	Color intesity;
	Tuple position;

	Color lighting(Material& material, Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow);

};