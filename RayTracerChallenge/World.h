#pragma once
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "Tuple.h"
#include "Color.h"
#include <set>
#include "Intersection.h"
#include "PreComputations.h"
#include "Normal.h"

class World {
public:

	Light light {Color(1, 1, 1), Tuple::point(-10, 10, -10)};
	std::vector<Shape*> objects;

	Color shadeHit(const Precomputations& comps, int& remaining, int& remainingRefraction) const;
	std::set <Intersection*, decltype(cmp)> worldIntersection(const Ray& ray)const;

	Color colorAt(const Ray& r, int remaining = 4, int remainingRefraction = 4)const;
	bool isShadowed(const Tuple& point)const;

	Color reflectedColor(const Precomputations& comps, int& remaining) const;
	Color refractedColor(const Precomputations& comps, int& remaining) const;
};

World defaultWorld();