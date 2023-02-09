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

	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		return Tuple::vector(0, 0, 0);
	}

	BoundingBox boundsOf(bool update = false) {
		return {};
	}

	// TODO: divide CSG
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

	inline Intersections filterIntersections(const Intersections& xs) {
		auto inl = false;
		auto inr = false;

		auto result = Intersections();

		for (auto intersection : xs.intersections) {
		
			// TODO: page 235 implement Group and CSG serach
			auto lhit = left->includes((Shape *)intersection->s);

			if (intersectionAllowed(operation, lhit, inl, inr)) {
				result.intersections.insert(intersection);
			}
			if (lhit) {
				inl = !inl;
			}
			else {
				inr = !inr;
			}	
		}

		return result;
	}

	inline Intersections intersect(const Ray& ray) {
		auto leftxs = left->shapeIntersect(ray);
		auto rightxs = right->shapeIntersect(ray);
		
		auto xs = Intersections();

		for (auto x : leftxs.intersections) {
			xs.intersections.insert(x);
		}

		for (auto x : rightxs.intersections) {
			xs.intersections.insert(x);
		}

		return filterIntersections(xs);
	}

	inline bool includes(const Shape* s) {
		return left->includes(s) || right->includes(s);
	}

};