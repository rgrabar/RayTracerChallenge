#pragma once

#include "BoundingBox.h"
#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuple.h"
#include <iostream>

class Shape {
public:

	// TODO: add == operator for all shapes

	inline virtual Intersections intersect(const Ray& ray)= 0;
	inline virtual Tuple objectNormal(const Tuple& worldPoint, const Intersection* hit = nullptr)= 0;
	inline virtual BoundingBox boundsOf(bool update = false)= 0;
	inline virtual void divide(int threashold = 1) = 0;
	inline virtual bool includes(const Shape* s) = 0;

	//TODO: make it a bit more clear that group overrides all other materials
	inline virtual void setMaterial(const Material& s) = 0;

	bool optOutShadow = 0;
	Shape* parent = nullptr;

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape() :origin(Tuple::point(0, 0, 0)) {}
	Shape(Tuple _origin) : origin(_origin) {}

	virtual ~Shape() = default;

	// TODO: shoud stripeatobject be part of material?
	inline Color stripeAtObject(const Tuple& worldPoint) {
		auto objectPoint = *transform.inverse() * worldPoint;
		auto patternPoint = *material.pattern->transform.inverse() * objectPoint;

		return material.pattern->patternColorAt(patternPoint);
	}

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

	inline Tuple normal(const Tuple& worldPoint, const Intersection* hit = nullptr) {
		/*
		auto objectPoint = *(s.transform.inverse()) * worldPoint;
		auto objectNormal = s.objectNormal(objectPoint);
		auto worldNormal = (*(s.transform.inverse())).transpose() * objectNormal;
		worldNormal.w = 0;
		return (worldNormal.normalize());
		*/

		auto localPoint = worldToObject(worldPoint);
		auto localNormal = objectNormal(localPoint, hit);

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