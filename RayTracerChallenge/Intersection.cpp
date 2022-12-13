#include "Intersection.h"

Intersection::Intersection(float _t, const void* _s) : t(_t), s(_s) {}

std::set<Intersection*, decltype(cmp)> intersections(cmp);

Intersection* Intersection::hit() {
	//sortIntersections();

	float maxT = INT_MAX;
	Intersection* ret = nullptr;

	for (auto& x : intersections) {
		if (x->t < 0)
			continue;
		if (x->t < maxT) {
			maxT = x->t;
			ret = x;
		}
	}

	if (ret != nullptr)
		return ret;

	return nullptr;
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
