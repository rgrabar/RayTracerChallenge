#include "World.h"
#include <iostream>
Color World::shadeHit(Precomputations& comps) {
	Sphere* x = (Sphere*)comps.shape;

	return x->material.lighting(light, comps.point, comps.eyev, comps.normalv);
}
//TODO: not sure if this should return intersect objects

std::set <Intersection, decltype(cmp1)> worldIntersection(World& w, Ray& ray) {

	std::set<Intersection, decltype(cmp1)> test(cmp1);

	for (auto object : w.objects) {
		ray = ray.transform(object->transform.inverse());

		auto sphereToRay = ray.origin - Tuple::point(0, 0, 0);
		auto a = ray.direction.dotProduct(ray.direction);
		auto b = 2 * ray.direction.dotProduct(sphereToRay);
		auto c = sphereToRay.dotProduct(sphereToRay) - 1;

		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
			return {};


		//TODO: make the first t the non negative smaller value

		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);

		// TODO: is this the best way to return?
		test.insert({ t1, object });
		test.insert({ t2, object });

	}
	return test;
}
