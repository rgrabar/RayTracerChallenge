#pragma once
#include "Shape.h"
#include <vector>
#include <iostream>
#include "Normal.h"
#include <algorithm>

class Group : public Shape {
public:
	//TODO: materials for groups

	std::vector<Shape*> children;

	void addChild(Shape& s) {
		children.emplace_back(&s);
		s.parent = this;
	
		// TODO: update bounds?
	}

	inline Intersections intersect(const Ray& ray) {

		if (!boundsOf().intersect(ray)) {
			return {};
		}

		Intersections i;

		for (auto shape : children) {
			// TODO: do this somehow else, overload intersect to take a vector?
			auto v = shape->shapeIntersect(ray);
			for (auto objectIntersect : v.intersections)
				i.intersections.insert(objectIntersect);
		}
		return i;
	}

	Tuple objectNormal(const Tuple& objectPoint) {
		return Tuple::vector(0, 0, 0);
	}

	BoundingBox boundsOf() {
		auto box = BoundingBox();

		for (auto shape : children) {
			auto cbox = shape->parentSpaceBoundsOf();
			box.mergeBox(cbox);
		}
		return box;
	}

	// TODO: do this better
	void inline partitionChildren(Group* leftG, Group* rightG) {
		BoundingBox left, right;

		auto bounds = boundsOf();
		bounds.splitBounds(&left, &right);

		std::vector<Shape*> newChildren;

		for (auto child : children) {
			auto childBounds = child->parentSpaceBoundsOf();
			if (left.boxContainsBox(childBounds)) {
				leftG->addChild(*child);
			}
			else if (right.boxContainsBox(childBounds)) {
				rightG->addChild(*child);
			}
			else
				newChildren.emplace_back(child);
		}
		children = newChildren;
	}
};