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

	std::vector<Light*> lights;
	std::vector<Shape*> objects;

	Color shadeHit(const Precomputations& comps, int& remaining, int& remainingRefraction) const;
	std::multiset <Intersection*, decltype(cmp)> worldIntersection(const Ray& ray)const;

	Color colorAt(const Ray& r, int remaining = 4, int remainingRefraction = 4)const;
	bool isShadowed(const Tuple& point, const Light* light)const;

	Color reflectedColor(const Precomputations& comps, int& remaining) const;
	Color refractedColor(const Precomputations& comps, int& remaining) const;
};

World defaultWorld();