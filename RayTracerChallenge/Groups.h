#pragma once
#include "Shape.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Group : public Shape {
public:
	//TODO: materials for groups

	std::vector<Shape*> children;
	BoundingBox m_bounds;

	~Group() {
		for (auto child : children) {
			if (dynamic_cast<Group*>(child)) {
				delete child;
			}
		}
	}

	//TODO: passing a local group variable as child
	// breaks everything yay
	void addChild(Shape* s) {
		children.emplace_back(s);
		s->parent = this;
	
		// TODO: update bounds if needed
		boundsOf(true);
	}

	inline Intersections intersect(const Ray& ray) {

		if (!m_bounds.intersect(ray)) {
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

	Tuple objectNormal(const Tuple& objectPoint, const Intersection* hit = nullptr) {
		return Tuple::vector(0, 0, 0);
	}

	BoundingBox boundsOf(bool update = false) {
		// TODO: cache the box, don't update if not needed
		if (update) {
			auto box = BoundingBox();

			for (auto shape : children) {
				auto cbox = shape->parentSpaceBoundsOf();
				box.mergeBox(cbox);
			}

			m_bounds = box;
		}
		return m_bounds;
	}

	// TODO: do this better
	void inline partitionChildren(Group& leftG, Group& rightG) {
		BoundingBox left, right;

		auto bounds = m_bounds;
		bounds.splitBounds(&left, &right);

		std::vector<Shape*> newChildren;

		for (auto child : children) {
			auto childBounds = child->parentSpaceBoundsOf();
			if (left.contains(childBounds)) {
				leftG.addChild(child);
			}
			else if (right.contains(childBounds)) {
				rightG.addChild(child);
			}
			else
				newChildren.emplace_back(child);
		}
		children = newChildren;
	}

	inline bool includes(const Shape* s) {
		return std::find(children.begin(), children.end(), s) != children.end();
	}

	inline void makeSubgroup(Group& sub) {
		auto g = new Group();
		for (auto s : sub.children) {
			g->addChild(s);
		}
		addChild(g);
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

	inline void setMaterial(const Material& s) {
		for (auto child : children) {
			child->setMaterial(s);
		}
	}
};