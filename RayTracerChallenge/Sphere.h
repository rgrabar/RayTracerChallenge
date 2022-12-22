#pragma once

#include "Shape.h"
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"

class Sphere : public Shape {

public:
	Sphere() : Shape(Tuple::point(0, 0, 0)) {}

	bool operator==(const Sphere& other) const;

	inline std::vector<Intersection> intersect(const Ray& ray) {

		auto rayCalc = ray.transform(transform.inverse());
		auto shapeToRay = rayCalc.origin - Tuple::point(0, 0, 0);
		auto a = rayCalc.direction.dotProduct(rayCalc.direction);
		auto b = 2 * rayCalc.direction.dotProduct(shapeToRay);
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
	Tuple normalAt(const Tuple& worldPoint) {
		auto objectPoint = transform.inverse() * worldPoint;
		auto objectNormal = objectPoint - Tuple::point(0, 0, 0);

		auto worldNormal = transform.inverse().transpose() * objectNormal;
		worldNormal.w = 0;

		return (worldNormal.normalize());
	}
};