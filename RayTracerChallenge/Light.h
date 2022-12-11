#pragma once

#include "Color.h"
#include "Tuple.h"

class Light {
public:
	
	Light(const Color& _intensity, const Tuple& _position);

	bool operator==(const Light& other) const;

	Color intesity;
	Tuple position;

};