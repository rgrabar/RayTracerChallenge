#pragma once

#include "Shape.h"
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"
#include <iostream>

class Sphere : public Shape {

public:
	Sphere() : Shape(Tuple::point(0, 0, 0)) {}

	bool operator==(const Sphere& other) const;

	inline std::vector<Intersection> intersect(const Ray& ray)const {

		
		auto shapeToRay = ray.origin - Tuple::point(0, 0, 0);
		auto a = ray.direction.dotProduct(ray.direction);
		auto b = 2 * ray.direction.dotProduct(shapeToRay);
		auto c = shapeToRay.dotProduct(shapeToRay) - 1;

		double discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
			return {};

		//TODO: make the first t the non negative smaller value

		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

		//TODO: not sure if I should add each record 
		//intersections.emplace_back(t1, s);
		//intersections.emplace_back(t2, s);

		/*std::vector<Intersection> retInter;
		retInter.emplace_back(t1, s);
		retInter.emplace_back(t2, s);
		*/
		return { {t1, this}, {t2, this} };
	}
	Tuple normalAt(const Tuple& objectPoint)const {
		return objectPoint - Tuple::point(0, 0, 0);
	}
};

inline Sphere glassSphere() {
	auto s = Sphere();
	s.transform = identityMatrix(4);
	s.material.transparency = 1.0;
	s.material.refractiveIndex = 1.5;
	
	return s;
}