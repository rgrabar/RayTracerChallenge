#pragma once

#include "Helper.h"
#include "Ray.h"
#include "Tuple.h"

#include <climits>
#include <limits>

class BoundingBox {
	// TODO: revise the bounding box code after adding triangles and CSG
public:
	Tuple boxMin;
	Tuple boxMax;

	struct MinMaxPoint {
		double tMin = INT_MAX, tMax = INT_MIN;
	};

	BoundingBox();
	BoundingBox(Tuple _boxMin, Tuple _boxMax);

	void addPoint(const Tuple& newPoint);
	void mergeBox(const BoundingBox& other);
	bool contains(const Tuple& point)const;
	bool contains(BoundingBox other)const;
	BoundingBox transform(const Matrix& transformMatrix)const;

	//TODO: reuse cube code somehow
	void checkAxis(MinMaxPoint& value, const double origin, const double direction, const double minB, const double maxB)const;
	bool intersect(const Ray& ray)const;
	void splitBounds(BoundingBox* left, BoundingBox* right)const;
};