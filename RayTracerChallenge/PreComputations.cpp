#include "PreComputations.h"
#include "Normal.h"
#include <iostream>

Precomputations::Precomputations(const Intersection& _intersection, const Ray& _ray) : 
	ray(_ray), 
	point(Tuple::point(0, 0, -1)), 
	eyev(Tuple::vector(0, 0, -1)), 
	normalv(Tuple::vector(0, 0, -1)) 
{
	t = _intersection.t;
	shape = _intersection.s;
	
	point = ray.position(t);
	eyev = -ray.direction;
	normalv = normal_at(*shape,point);

	if (normalv.dotProduct(eyev) < 0) {
		inside = true;
		normalv = -normalv;
	}
	else
		inside = false;
}