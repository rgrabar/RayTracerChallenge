#pragma once

#include "BoundingBox.h"
#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuple.h"
#include <iostream>

struct Shape {

	// TODO: add == operator for all shapes

	virtual Intersections intersect(const Ray& ray)const = 0;
	virtual Tuple objectNormal(const Tuple& worldPoint, const Intersection* hit = nullptr)const = 0;
	virtual BoundingBox boundsOf(bool update = false) = 0;
	virtual void divide(int threashold = 1) = 0;
	virtual bool includes(const Shape* s)const = 0;

	//TODO: make it a bit more clear that group overrides all other materials
	virtual void setMaterial(const Material& s) = 0;
	//TODO: should this be = 0? also add UVmap for triangles and textures
	virtual void UVmap([[maybe_unused]]const Tuple& p, [[maybe_unused]]double* u, [[maybe_unused]]double* v) const {}

	bool optOutShadow = 0;
	Shape* parent = nullptr;

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape() :origin(Tuple::point(0, 0, 0)) {}
	Shape(Tuple _origin) : origin(_origin) {}

	virtual ~Shape() = default;

	// TODO: shoud stripeatobject be part of material?  rename this 
	inline Color stripeAtObject(const Tuple& worldPoint) {
		auto objectPoint = *transform.inverse() * worldPoint;
		auto patternPoint = *material.pattern->transform.inverse() * objectPoint;

		return material.pattern->patternColorAt(patternPoint, this);
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

	inline BoundingBox parentSpaceBoundsOf([[maybe_unused]] bool update = false) {
		return boundsOf().transform(transform);
	}

	inline void shapeDivide(int threashold = 1) {
		divide(threashold);
		return;
	}
};