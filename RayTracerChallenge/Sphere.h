#pragma once
#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"

#include <utility>
#include <optional>
#include <functional>

class Sphere
{

public:
	Tuple origin;

	Sphere() :origin(Tuple::point(0, 0, 0)) {}
	Matrix transform = identityMatrix(4);

	Material material;
};