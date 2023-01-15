#pragma once

#include <limits>
#include "Tuple.h"

class BoundingBox {

public:
	Tuple boxMin;
	Tuple boxMax;

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

};