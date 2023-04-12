#pragma once
#include "Shape.h"
#include "Helper.h"
#include <algorithm>    // std::swap
#include <cmath>
#include <climits>

namespace cubeFace {
	enum FACE {
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}

struct Cube : public Shape {
	
	struct MinMaxPoint {
		double tMin = INT_MAX, tMax = INT_MIN;
	};

	Cube();
	void checkAxis(MinMaxPoint& value, double origin, double direction)const;

	Intersections intersect(const Ray& ray)const override;
	Tuple objectNormal(const Tuple& objectPoint, [[maybe_unused]] const Intersection* hit = nullptr)const override;
	BoundingBox boundsOf([[maybe_unused]] bool update = false)override;
	void divide([[maybe_unused]] int threashold = 1) override;
	bool includes(const Shape* s)const override;
	void setMaterial(const Material& s)override;

	static cubeFace::FACE faceFromPoint(const Tuple& point) {
		auto absX = std::abs(point.x);
		auto absY = std::abs(point.y);
		auto absZ = std::abs(point.z);

		auto coord = std::max({ absX, absY, absZ });

		if (coord == point.x)
			return cubeFace::RIGHT;
		if (coord == -point.x)
			return cubeFace::LEFT;
		if (coord == point.y)
			return cubeFace::UP;
		if (coord == -point.y)
			return cubeFace::DOWN;
		if (coord == point.z)
			return cubeFace::FRONT;

		return cubeFace::BACK;
	}

	void cubeUVFront(const Tuple& point, double* u, double* v)const;
	void cubeUVBack(const Tuple& point, double* u, double* v)const;
	void cubeUVLeft(const Tuple& point, double* u, double* v)const;
	void cubeUVRight(const Tuple& point, double* u, double* v)const;
	// The X is wrong in the example i think for both up and down
	void cubeUVUp(const Tuple& point, double* u, double* v)const;
	void cubeUVDown(const Tuple& point, double* u, double* v)const;

	void UVmap(const Tuple& p, double* u, double* v) const override;

};