#pragma once
#include "Shape.h"
#include <vector>
#include <iostream>

class Group : public Shape {
public:
	std::vector<Shape*> children;

	void addChild(Shape& s) {
		children.emplace_back(&s);
		s.parent = this;
	}

	inline std::vector<Intersection> intersect(const Ray& ray) {

		std::vector<Intersection> inter;
		Intersections i;

		for (auto shape : children) {
			// TODO: do this somehow else, overload intersect to take a vector?
			auto v = shape->intersect(ray);
				if(v.size() != 0)
					for (auto objectIntersect : v) {
						inter.emplace_back(objectIntersect);
						i.intersections.insert(&objectIntersect);
					}
		}

		std::cout << "SSSSSSSSSSSSSSSSS" << i.intersections.size() << "\n";

		return inter;
	}

	Tuple normalAt(const Tuple& objectPoint) {
		return Tuple::vector(0, 0, 0);
	}

};