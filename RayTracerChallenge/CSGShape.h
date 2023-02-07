#pragma once
#include <string>
#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"

class CSGShape : public Shape{
public:
	std::string operation;
	Shape* left;
	Shape* right;

	CSGShape(std::string _operation, Shape* _left, Shape* _right) : operation(_operation), left(_left), right(_right) {
		left->parent = this;
		right->parent = this;
	}


	//TODO: replace tmp functions

	inline Intersections intersect(const Ray& ray) {
		return {};
	}
	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		return Tuple::vector(0, 0, 0);
	}

	BoundingBox boundsOf(bool update = false) {
		return {};
	}

	inline void divide(int threashold = 1) {
	}

	inline bool intersectionAllowed(std::string op, bool lhit, bool inl, bool inr) {
		if (op == "union") {
			return (lhit && !inr) || (!lhit && !inl);
		}
		else if (op == "intersection") {
			return (lhit && inr) || (!lhit && inl);
		}
		else if (op == "difference") {
			return (lhit && !inr) || (!lhit && inl);
		}

		return false;
	}

};