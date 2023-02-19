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
	inline virtual Tuple objectNormal(const Tuple& worldPoint, const Intersection* hit = nullptr)= 0;
	inline virtual BoundingBox boundsOf(bool update = false)= 0;
	inline virtual void divide(int threashold = 1) = 0;
	inline virtual bool includes(const Shape* s) = 0;

	Shape* parent = nullptr;

	Matrix transform = identityMatrix(4);
	Material material;
	Tuple origin;

	Shape() :origin(Tuple::point(0, 0, 0)) {}
	Shape(Tuple _origin) : origin(_origin) {}

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

	inline Color lighting(const Light* light, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow) {

		Color newColor = material.color;

		if (material.pattern != nullptr)
			newColor = stripeAtObject(point);

		auto effectiveColor = newColor * light->intesity;
		auto lightv = (light->position - point).normalize();
		auto ambientColor = effectiveColor * material.ambient;
		auto lightDotNormal = lightv.dotProduct(normalv);

		Color diffuseColor(0, 0, 0);
		Color specularColor(0, 0, 0);

		if (lightDotNormal < 0) {
			diffuseColor = Color(0, 0, 0);
			specularColor = Color(0, 0, 0);
		}
		else {
			diffuseColor = effectiveColor * material.diffuse * lightDotNormal;
			auto reflectv = -lightv.reflect(normalv);
			auto reflectDotEye = reflectv.dotProduct(eyev);

			if (reflectDotEye <= 0)
				specularColor = Color(0, 0, 0);
			else {
				auto factor = pow(reflectDotEye, material.shininess);
				specularColor = light->intesity * material.specular * factor;
			}
		}

		auto test = ambientColor + diffuseColor + specularColor;

		if (inShadow)
			return ambientColor;
		else
			return ambientColor + diffuseColor + specularColor;
	}
};