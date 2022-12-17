#include "World.h"
#include <iostream>
Color World::shadeHit(const Precomputations& comps) const{

	return (comps.shape)->material.lighting(light, comps.point, comps.eyev, comps.normalv);
}
//TODO: not sure if this should return intersect objects

std::set <Intersection*, decltype(cmp)> World::worldIntersection(const Ray& ray)const{

	std::set<Intersection*, decltype(cmp)> intersections(cmp);

	for (auto object : objects) {
		auto rayToSphere = ray.transform(object->transform.inverse());

		auto shapeToRay = rayToSphere.origin - Tuple::point(0, 0, 0);
		auto a = rayToSphere.direction.dotProduct(rayToSphere.direction);
		auto b = 2 * rayToSphere.direction.dotProduct(shapeToRay);
		auto c = shapeToRay.dotProduct(shapeToRay) - 1;

		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
			return {};


		//TODO: make the first t the non negative smaller value

		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);

		auto tmp = new Intersection(t1, object);
		auto tmp1 = new Intersection(t2, object);

		// TODO: is this the best way to return?
		intersections.insert(tmp);
		intersections.insert(tmp1);

	}
	return intersections;
}

Color World::colorAt(const Ray& r)const {
	auto intWorld = worldIntersection(r);
	Intersections i(intWorld);

	Intersection* ht = i.hit();
	if (ht == nullptr)
		return Color(0, 0, 0);

	Precomputations p(*ht, r);

	return shadeHit(p);
}