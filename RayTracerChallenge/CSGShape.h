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
	BoundingBox m_bounds;

	CSGShape(std::string _operation, Shape* _left, Shape* _right) : operation(_operation), left(_left), right(_right) {
		left->parent = this;
		right->parent = this;
	}

	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		// CSG returns normal of primitive shape, this shouldn't happen
		assert(false);
		return Tuple::vector(0, 0, 0);
	}

	// TODO: cache bounds?
	inline void divide(int threashold = 1) {
		right->divide();
		left->divide();
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
		if (!m_bounds.intersect(ray)) {
			return {};
		}
		auto leftxs = left->shapeIntersect(ray);
		auto rightxs = right->shapeIntersect(ray);
		
		auto xs = Intersections();

		xs.intersections.insert(leftxs.intersections.begin(), leftxs.intersections.end());
		xs.intersections.insert(rightxs.intersections.begin(), rightxs.intersections.end());

		return filterIntersections(xs);
	}

	inline bool includes(const Shape* s) {
		return left->includes(s) || right->includes(s);
	}

	BoundingBox boundsOf(bool update = false) {
		// TODO: cache the box, don't update if not needed
		// TODO: check if it works
		auto box = BoundingBox();

		auto rBox = right->parentSpaceBoundsOf();
		auto lBox = left->parentSpaceBoundsOf();

		box.mergeBox(rBox);
		box.mergeBox(lBox);

		m_bounds = box;

		return m_bounds;
	}

	inline void setMaterial(const Material& s) {
		right->material = s;
		left->material = s;
	}

};