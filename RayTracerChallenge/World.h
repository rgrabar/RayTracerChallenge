#pragma once
#include "Color.h"
#include "Intersection.h"
#include "Light.h"
#include "PreComputations.h"
#include "Sphere.h"
#include "Tuple.h"
#include <set>
#include <vector>

class World {
public:

	std::vector<Light*> lights;
	std::vector<Shape*> objects;

	Color shadeHit(const Precomputations& comps, int& remaining, int& remainingRefraction) const;
	std::multiset <Intersection*, cmp> worldIntersection(const Ray& ray)const;

	Color colorAt(const Ray& r, int remaining = 4, int remainingRefraction = 4)const;
	bool isShadowed(const Tuple& point, const Tuple& lightPosition)const;

	Color reflectedColor(const Precomputations& comps, int& remaining) const;
	Color refractedColor(const Precomputations& comps, int& remaining) const;
};

World defaultWorld();