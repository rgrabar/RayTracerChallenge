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
	}

	inline Intersections intersect(const Ray& ray) {

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
		//TODO: replace this placeholder
		return BoundingBox(Tuple::point(0, 0, 0), Tuple::point(0, 0, 0));
	}

};