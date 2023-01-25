#include "PreComputations.h"
#include "Normal.h"
#include <iostream>

Precomputations::Precomputations() :point(Tuple::point(0, 0, -1)),
// TODO: fix default constructor
ray(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1)),
eyev(Tuple::vector(0, 0, -1)),
normalv(Tuple::vector(0, 0, -1)),
// TODO: this should not be a default
overPoint(Tuple::vector(0, 0, 0)),
reflectv(Tuple::point(0, 0, 0)),
underPoint(Tuple::vector(0, 0, 0))
{}

Precomputations::Precomputations(const Intersection& _intersection, const Ray& _ray, const Intersections& intersections) :
	ray(_ray),
	point(Tuple::point(0, 0, -1)),
	eyev(Tuple::vector(0, 0, -1)),
	normalv(Tuple::vector(0, 0, -1)),
	// TODO: this should not be a default
	overPoint(Tuple::vector(0, 0, 0)),
	reflectv(Tuple::point(0, 0, 0)),
	underPoint(Tuple::vector(0, 0, 0))
{
	// TODO: use a better data structure for container	
	for (auto x : intersections.intersections) {
		if (x == &_intersection) {
			if (container.size() == 0) {
				n1 = 1.0;
			}
			else {
				n1 = ((Shape*)container[container.size() - 1])->material.refractiveIndex;
			}
		}

		auto it = std::find(container.begin(), container.end(), x->s);
		if (it != container.end()) {
			container.erase(it);
		}
		else {
			container.emplace_back((Shape * )x->s);
		}

		if (x == &_intersection) {
			if (container.size() == 0) {
				n2 = 1.0;
			}
			else {
				n2 = ((Shape*)container[container.size() - 1])->material.refractiveIndex;
			}
			break;
		}
	}

	//std::cout << "n1: " << n1 << "\n";
	//std::cout << "n2: " << n2 << "\n";
	
	t = _intersection.t;
	shape = ((Shape*)_intersection.s);
	
	point = ray.position(t);
	eyev = -ray.direction;
	normalv = shape->normal(point);

	if (normalv.dotProduct(eyev) < 0) {
		inside = true;
		normalv = -normalv;
	}
	else
		inside = false;

	reflectv = ray.direction.reflect(normalv);
	
	overPoint = point + normalv * (EPSILON);
	underPoint = point - normalv * (EPSILON);
}

double Precomputations::schlick()const {
	auto cos = eyev.dotProduct(normalv);

	if (n1 > n2) {
		auto n = n1 / n2;
		auto sin2T = n * n * (1.0 - cos * cos);

		if (sin2T > 1.0)
			return 1.0;

		cos = sqrt(1.0 - sin2T);
	}

	auto r0 = pow(((n1 - n2) / (n1 + n2)), 2);

	return r0 + (1 - r0) * pow(1 - cos, 5);
}