#pragma once

#include "Color.h"
#include "Tuple.h"

class Light {
public:
	
	Light(Color _intensity, Tuple _position);

	Color intesity;
	Tuple position;

};