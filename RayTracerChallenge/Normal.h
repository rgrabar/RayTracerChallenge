#pragma once

#include "Sphere.h"
#include "Tuple.h"

Tuple normal_at(Sphere s, Tuple worldPoint);

Tuple reflect(Tuple in, Tuple normal);