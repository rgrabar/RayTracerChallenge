#pragma once

#include "Sphere.h"
#include "Tuple.h"
#include "Intersection.h"

Tuple reflect(const Tuple& in, const Tuple& normal);

//TODO: move this in some appropriate class, can't have it in "Pattern.h" because of a circular dependency with shape.h
Color stripeAtObject(Shape* object, Tuple& worldPoint);

//TODO: move this in some appropriate class, can't have it in "Material.h" because of a circular dependency with shape.h
Color lighting(Shape* object, const Light& light, const Tuple& point, const Tuple& eyev, const Tuple& normalv, const bool inShadow);