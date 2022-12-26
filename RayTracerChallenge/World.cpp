#include "World.h"
#include <iostream>
Color World::shadeHit(const Precomputations& comps) const{

	auto shadowed = isShadowed(comps.overPoint);
	// TODO: sending comps.point instead of comps.overPoint causes acne
	return lighting(comps.shape, light, comps.overPoint, comps.eyev, comps.normalv, shadowed);
}
//TODO: not sure if this should return intersect objects

std::set <Intersection*, decltype(cmp)> World::worldIntersection(const Ray& ray)const{

	std::set<Intersection*, decltype(cmp)> intersections(cmp);

	for (auto object : objects) {

		auto a = intersect(object, ray);

		if (a.size() == 0)
			continue;
		if (a.size() == 1) {
			// TODO: ZASTO NE MOREDULEN SAMO &a[0]??
			auto tmp = new Intersection(a[0].t, a[0].s);
			intersections.insert(tmp);
			
		}
		else {
			auto tmp = new Intersection(a[0].t, a[0].s);
			auto tmp1 = new Intersection(a[1].t, a[1].s);
			intersections.insert(tmp);
			intersections.insert(tmp1);
		}
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

bool World::isShadowed(const Tuple& point)const {
	auto v = light.position - point;
	auto distance = v.magnitude();
	auto direction = v.normalize();

	auto r = Ray(point, direction);

	auto intersections = worldIntersection(r);
	Intersections i(intersections);

	auto h = i.hit();
	if (h != nullptr && h->t < distance)
		return true;
	return false;
}