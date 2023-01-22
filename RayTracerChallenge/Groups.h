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

	// TODO: overload this? with Shape*
	void addChild(Shape& s) {
		children.emplace_back(&s);
		s.parent = this;
	
		// TODO: update bounds if needed
		boundsOf();
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
		// TODO: cache the box, don't update if not needed
		auto box = BoundingBox();

		for (auto shape : children) {
			auto cbox = shape->parentSpaceBoundsOf();
			box.mergeBox(cbox);
		}
		return box;
	}

	// TODO: do this better
	void inline partitionChildren(Group& leftG, Group& rightG) {
		BoundingBox left, right;

		auto bounds = boundsOf();
		bounds.splitBounds(&left, &right);

		std::vector<Shape*> newChildren;

		for (auto child : children) {
			auto childBounds = child->parentSpaceBoundsOf();
			if (left.boxContainsBox(childBounds)) {
				leftG.addChild(*child);
			}
			else if (right.boxContainsBox(childBounds)) {
				rightG.addChild(*child);
			}
			else
				newChildren.emplace_back(child);
		}
		children = newChildren;
	}

	inline void makeSubgroup(Group& sub) {
		// TODO leak?
		auto g = new Group();
		for (auto s : sub.children) {
			g->addChild(*s);
		}
		addChild(*g);
	}

	inline void divide(int threashold = 1)override {

		if (threashold <= children.size()) {
			auto left = Group();
			auto right = Group();

			partitionChildren(left, right);
			if (left.children.size() != 0) {
				makeSubgroup(left);
			}
			if (right.children.size() != 0) {
				makeSubgroup(right);
			}
		}

		for (auto child : children) {
			child->shapeDivide(threashold);
		}

	}
};