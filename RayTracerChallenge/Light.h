#pragma once

#include "Color.h"
#include "Tuple.h"

class Light {
public:
	
	Light(const Color& _intensity, const Tuple& _position);

	Color intesity;
	Tuple position;

};