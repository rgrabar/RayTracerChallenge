#pragma once
#include "Tuple.h"
#include "Ray.h"

#include <utility>
#include <optional>
#include <functional>

class Sphere
{

public:
	Tuple origin;

	Sphere() :origin(Tuple::point(0, 0, 0)) {}

};