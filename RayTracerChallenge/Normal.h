#pragma once

#include "Sphere.h"
#include "Tuple.h"

Tuple normal_at(const Shape& s, const Tuple& worldPoint);
Tuple reflect(const Tuple& in, const Tuple& normal);