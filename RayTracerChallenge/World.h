#pragma once
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "Tuple.h"
#include "Color.h"
#include <set>
#include "Intersection.h"
#include "PreComputations.h"

class World {
public:


	Light light {Color(1, 1, 1), Tuple::point(-10, 10, -10)};
	std::vector<Sphere*> objects;

	Color shadeHit(Precomputations& comps);
};

std::set <Intersection, decltype(cmp1)> worldIntersection(World& w, Ray& ray);