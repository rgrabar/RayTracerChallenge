#pragma once

#include "Shape.h"

struct Sphere : public Shape {

	Sphere();

	bool operator==(const Sphere& other) const;

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1)override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;

	void UVmap(const Tuple& p, double* u, double* v)const override;

};

inline Sphere glassSphere() {
	auto s = Sphere();
	s.transform = identityMatrix(4);
	s.material.transparency = 1.0;
	s.material.refractiveIndex = 1.5;
	
	return s;
}