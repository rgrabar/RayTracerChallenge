#pragma once

#include <limits>
#include "Tuple.h"

class BoundingBox {
	// TODO: revise the bounding box code after adding triangles and CSG
public:
	Tuple boxMin;
	Tuple boxMax;

	struct MinMaxPoint {
		double tMin = INT_MAX, tMax = INT_MIN;
	};

	BoundingBox() : boxMin(Tuple::point(INFINITY, INFINITY, INFINITY)),
					boxMax(Tuple::point(-INFINITY, -INFINITY, -INFINITY))
	
	{
	
	}

	BoundingBox(Tuple _boxMin, Tuple _boxMax) : boxMin(_boxMin), boxMax(_boxMax) {}

	void addPoint(const Tuple& newPoint) {
		if (newPoint.x < boxMin.x)
			boxMin.x = newPoint.x;

		if (newPoint.y < boxMin.y)
			boxMin.y = newPoint.y;

		if (newPoint.z < boxMin.z)
			boxMin.z = newPoint.z;
	
	
		if (newPoint.x > boxMax.x)
			boxMax.x = newPoint.x;

		if (newPoint.y > boxMax.y)
			boxMax.y = newPoint.y;

		if (newPoint.z > boxMax.z)
			boxMax.z = newPoint.z;
	}

	void mergeBox(const BoundingBox& other) {
		addPoint(other.boxMin);
		addPoint(other.boxMax);
	}

	bool boxContainsPoint(const Tuple& point) {
		return boxMin.x <= point.x && point.x <= boxMax.x
			&& boxMin.y <= point.y && point.y <= boxMax.y
			&& boxMin.z <= point.z && point.z <= boxMax.z;
	}

	bool boxContainsBox(BoundingBox other) {
		return boxContainsPoint(other.boxMin) &&
			   boxContainsPoint(other.boxMax);
	}

	BoundingBox transform(const Matrix& transformMatrix) {
		
		Tuple pointArr[] = {
			boxMin,
			Tuple::point(boxMin.x, boxMin.y, boxMax.z),
			Tuple::point(boxMin.x, boxMax.y, boxMin.z),
			Tuple::point(boxMin.x, boxMax.y, boxMax.z),
			Tuple::point(boxMax.x, boxMin.y, boxMin.z),
			Tuple::point(boxMax.x, boxMin.y, boxMax.z),
			Tuple::point(boxMax.x, boxMax.y, boxMin.z),
			boxMax
		};

		auto newBox = BoundingBox();
		for (int i = 0; i < 8; ++i) {
			newBox.addPoint(transformMatrix * pointArr[i]);
		}

		return newBox;
	}

	//TODO: reuse cube code somehow

	void checkAxis(MinMaxPoint& value, const double origin, const double direction, const double minB, const double maxB) {
		auto tminNumerator = (minB - origin);
		auto tmaxNumerator = (maxB - origin);

		if (fabs(direction) >= EPSILON) {
			value.tMin = tminNumerator / direction;
			value.tMax = tmaxNumerator / direction;
		}
		else {
			value.tMin = tminNumerator * INFINITY;
			value.tMax = tmaxNumerator * INFINITY;
		}

		if (value.tMin > value.tMax) {
			auto tmp = value.tMax;
			value.tMax = value.tMin;
			value.tMin = tmp;
		}
	}

	inline bool intersect(const Ray& ray) {

		MinMaxPoint tmp;

		checkAxis(tmp, ray.origin.x, ray.direction.x, boxMin.x, boxMax.x);
		auto [xTmin, xTmax] = tmp;

		checkAxis(tmp, ray.origin.y, ray.direction.y, boxMin.y, boxMax.y);
		auto [yTmin, yTmax] = tmp;

		checkAxis(tmp, ray.origin.z, ray.direction.z, boxMin.z, boxMax.z);
		auto [zTmin, zTmax] = tmp;

		auto tmin = std::fmax(xTmin, std::fmax(yTmin, zTmin));
		auto tmax = std::fmin(xTmax, std::fmin(yTmax, zTmax));

		if (tmin > tmax)
			return false;

		return true;
	}


};