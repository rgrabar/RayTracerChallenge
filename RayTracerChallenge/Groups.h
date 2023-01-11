#pragma once
#include "Shape.h"
#include <vector>
#include <iostream>
#include "Normal.h"
#include <algorithm>

// todo: do this nicer
inline static bool compareIntersection(const Intersection& a, const Intersection& b) {
	return a.t < b.t;
}

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
			auto v = shape->shapeIntersect(ray);
				if(v.size() != 0)
					for (auto objectIntersect : v) {
						inter.emplace_back(objectIntersect);
						i.intersections.insert(&objectIntersect);
					}
		}
		sort(inter.begin(), inter.end(), compareIntersection);
		return inter;
	}

	Tuple objectNormal(const Tuple& objectPoint) {
		return Tuple::vector(0, 0, 0);
	}

};