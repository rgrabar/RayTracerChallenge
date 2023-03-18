#include "World.h"
#include <iostream>
#include "Helper.h"
#include "Transformations.h"

Color World::shadeHit(const Precomputations& comps, int& remaining, int& remainingRefraction) const{

	auto surface = Color(0, 0, 0);
	
	// TODO: sending comps.point instead of comps.overPoint causes acne
	for (auto light : lights) {
	//	auto shadowed = isShadowed(comps.overPoint, light->position);
		auto intensityAt = light->intensityAt(comps.overPoint, *this);
		surface = surface + light->lighting(comps.shape->material, comps.shape, comps.overPoint, comps.eyev, comps.normalv, intensityAt);
	}

	//TODO: should i divide? don't think so 
	//surface = surface / (double)lights.size();
	
	auto reflected = reflectedColor(comps, remaining, remainingRefraction);
	auto refracted = refractedColor(comps, remaining, remainingRefraction);

	auto material = comps.shape->material;

	if (material.reflective > 0 && material.transparency > 0) {
		auto reflectance = comps.schlick();
		auto clr = surface + reflected * reflectance + refracted * (1 - reflectance);
		//std::cout  << surface.r << " " << surface.g << " " << surface.b << " " << " " << refracted.r <<" " << refracted.g << " " << refracted.b << " " << reflectance << "\n";
		return clr;
	}

	return surface + reflected + refracted;
}
//TODO: not sure if this should return intersect objects

std::multiset <Intersection*, cmp> World::worldIntersection(const Ray& ray)const {

	std::multiset<Intersection*, cmp> intersections;

	for (auto object : objects) {

		auto a = object->shapeIntersect(ray);
		for (auto tmp : a.intersections) {
			intersections.insert(tmp);
		}
	}
	return intersections;
}

Color World::colorAt(const Ray& r, int remaining, int remainingRefraction)const {
	auto intWorld = worldIntersection(r);
	Intersections i(intWorld);

	Intersection* ht = i.hit();
	Color c = Color(0, 0, 0);
	
	if (ht != nullptr) {
		Precomputations p(*ht, r, i);
		c = shadeHit(p, remaining, remainingRefraction);
	}

	// TODO: leak?
	for (auto tmp : i.intersections)
		delete tmp;

	i.intersections.clear();
	
	return c;

}

bool World::isShadowed(const Tuple& point, const Tuple& lightPosition)const {
	bool inShadow = false;
	
	auto v = lightPosition - point;
	auto distance = v.magnitude();
	auto direction = v.normalize();

	auto r = Ray(point, direction);

	auto intersections = worldIntersection(r);
	Intersections i(intersections);

	auto h = i.hit(true);
	if (h != nullptr && h->t < distance)
		inShadow = true;
	
	if (h != nullptr) {
		auto s = (Shape*)h->s;

		// TODO can i do this somewhere else?
		if (s->optOutShadow)
			inShadow = false;
	}

	for (auto tmp : i.intersections)
		delete tmp;

	return inShadow;
}

Color World::reflectedColor(const Precomputations& comps, int& remaining, int remainingRefraction)const {
	
	if (remaining <= 0)
		return Color(0, 0, 0);
	
	if (epsilonEqual(comps.shape->material.reflective, 0)) {
		return Color(0, 0, 0);
	}

	auto reflectedRay = Ray(comps.overPoint, comps.reflectv);
	auto color = colorAt(reflectedRay, remaining - 1, remainingRefraction);

	//std::cout << color.r << " " << color.g << " " << color.b << "\n";

	return color * comps.shape->material.reflective;
}

Color World::refractedColor(const Precomputations& comps, int& remaining, int remainingRefraction) const {

	if (remainingRefraction <= 0) {
		//std::cout << "remaining less than 0\n";
		return Color(0, 0, 0);
	}
	if (epsilonEqual(comps.shape->material.transparency, 0)) {
		//std::cout << "Transparency is 0\n";
		return Color(0, 0, 0);
	}

	auto nRatio = comps.n1 / comps.n2;
	//std::cout << "RATIO " << nRatio << "\n";
	auto cosI = comps.eyev.dotProduct(comps.normalv);

	auto sin2T = nRatio * nRatio * (1 - cosI * cosI);

	if (sin2T > 1) {
		return Color(0, 0, 0);
	}
	auto cosT = sqrt(1.0 - sin2T);
	auto direction = comps.normalv * (nRatio * cosI - cosT) - comps.eyev * nRatio;

	auto refractRay = Ray(comps.underPoint, direction);

	auto refractColor = colorAt(refractRay, remaining, remainingRefraction - 1) * comps.shape->material.transparency;

	//std::cout << "legit color\n";
	//std::cout << refractColor.r << " " << refractColor.g << " " << refractColor.b << "\n";
	return refractColor;
}

World defaultWorld() {

	Sphere* s1 = new Sphere();
	Sphere* s2 = new Sphere();
	s1->material.color = Color(0.8, 1.0, 0.6);
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;

	s2->transform = scale(0.5, 0.5, 0.5);

	World w;
	w.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));

	w.objects.emplace_back(s1);
	w.objects.emplace_back(s2);

	return w;
}