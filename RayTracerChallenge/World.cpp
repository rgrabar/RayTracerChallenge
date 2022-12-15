#include "World.h"
#include <iostream>
Color World::shadeHit(Precomputations& comps) {
	//TODO: ovo lipje
	Shape* x = comps.shape;

	return x->material.lighting(light, comps.point, comps.eyev, comps.normalv);
}
//TODO: not sure if this should return intersect objects

std::set <Intersection, decltype(cmp1)> worldIntersection(World& w, Ray& ray) {

	std::set<Intersection, decltype(cmp1)> intersections(cmp1);

	for (auto object : w.objects) {
		ray = ray.transform(object->transform.inverse());

		auto shapeToRay = ray.origin - Tuple::point(0, 0, 0);
		auto a = ray.direction.dotProduct(ray.direction);
		auto b = 2 * ray.direction.dotProduct(shapeToRay);
		auto c = shapeToRay.dotProduct(shapeToRay) - 1;

		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
			return {};


		//TODO: make the first t the non negative smaller value

		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);

		// TODO: is this the best way to return?
		intersections.insert({ t1, object });
		intersections.insert({ t2, object });

	}
	return intersections;
}
