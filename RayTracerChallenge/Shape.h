#pragma once

#include "Matrix.h"
#include "Material.h"
#include "Tuple.h"
#include "Intersection.h"
#include "Ray.h"
#include <iostream>
#include "BoundingBox.h"
#include <iostream>

class Shape {
public:

	inline virtual Intersections intersect(const Ray& ray)= 0;
	inline virtual Tuple objectNormal(const Tuple& worldPoint)= 0;
	inline virtual BoundingBox boundsOf(bool update = false)= 0;
	inline virtual void divide(int threashold = 1) = 0;

	Shape* parent = nullptr;

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape() :origin(Tuple::point(0, 0, 0)) {}
	Shape(Tuple _origin) : origin(_origin) {}

	
	inline Tuple normalToWorld(const Tuple& normal) {
		Tuple worldNormal = normal;
		worldNormal = transform.inverse()->transpose() * worldNormal;
		worldNormal.w = 0;

		worldNormal = worldNormal.normalize();

		if (parent != nullptr) {
			worldNormal = parent->normalToWorld(worldNormal);
		}

		return worldNormal;
	}

	inline Tuple worldToObject(const Tuple& point) {
		
		Tuple worldPoint = point;

		if (parent != nullptr) {
			worldPoint = parent->worldToObject(worldPoint);
		}

		return *(transform.inverse()) * worldPoint;
	}

	inline Intersections shapeIntersect(const Ray& ray) {
		return intersect(ray.transform(*transform.inverse()));
	};


	inline Tuple normal(const Tuple& worldPoint) {
		/*
		auto objectPoint = *(s.transform.inverse()) * worldPoint;
		auto objectNormal = s.objectNormal(objectPoint);
		auto worldNormal = (*(s.transform.inverse())).transpose() * objectNormal;
		worldNormal.w = 0;
		return (worldNormal.normalize());
		*/

		auto localPoint = worldToObject(worldPoint);
		auto localNormal = objectNormal(localPoint);

		return normalToWorld(localNormal);
	}

	inline BoundingBox parentSpaceBoundsOf(bool update = false) {
		return boundsOf().transform(transform);
	}

	inline void shapeDivide(int threashold = 1) {
		divide(threashold);
		return;
	}
};