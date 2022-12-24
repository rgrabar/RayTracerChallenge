#pragma once

#include "Sphere.h"
#include "Tuple.h"
#include "Intersection.h"

Tuple normal_at(const Shape& s, const Tuple& worldPoint);
Tuple reflect(const Tuple& in, const Tuple& normal);

//TODO: move this in some appropriate class, can't have it in "intersection.h" because of a circular dependency with shape.h
std::vector<Intersection> intersect(const Shape* object, const Ray& ray);