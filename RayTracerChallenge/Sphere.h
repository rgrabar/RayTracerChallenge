#pragma once

#include "Shape.h"

class Sphere : public Shape {

public:
	Sphere() : Shape(Tuple::point(0, 0, 0)) {}

	bool operator==(const Sphere& other) const;

	inline Intersections intersect(const Ray& ray) {

		auto shapeToRay = ray.origin - Tuple::point(0, 0, 0);
		auto a = ray.direction.dotProduct(ray.direction);
		auto b = 2 * ray.direction.dotProduct(shapeToRay);
		auto c = shapeToRay.dotProduct(shapeToRay) - 1;

		double discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
			return {};

		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

		Intersection* i1 = new Intersection(t1, this);
		Intersection* i2 = new Intersection(t2, this);

		Intersections inter;
		inter.intersections.insert(i1);
		inter.intersections.insert(i2);

		/*std::vector<Intersection> retInter;
		retInter.emplace_back(t1, s);
		retInter.emplace_back(t2, s);
		*/
		return inter;
	}
	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		return objectPoint - Tuple::point(0, 0, 0);
	}

	BoundingBox boundsOf(bool update = false) {
		return BoundingBox(Tuple::point(-1, -1, -1), Tuple::point(1, 1, 1));
	}

	inline void divide(int threashold = 1) {
		return;
	}

	inline bool includes(const Shape* s) {
		return this == s;
	}

	inline void setMaterial(const Material& s) {
		material = s;
	}

};

inline Sphere glassSphere() {
	auto s = Sphere();
	s.transform = identityMatrix(4);
	s.material.transparency = 1.0;
	s.material.refractiveIndex = 1.5;
	
	return s;
}