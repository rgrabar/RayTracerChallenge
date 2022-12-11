#pragma once
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "Tuple.h"
#include "Color.h"

class World {
public:


	Light light {Color(1, 1, 1), Tuple::point(-10, 10, -10)};
	std::vector<Sphere*> objects;
};