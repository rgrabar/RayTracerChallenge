#pragma once
#include "Matrix.h"
#include <math.h>

Matrix translate(double x, double y, double z);
Matrix scale(double x, double y, double z);
// angle is in radians
Matrix rotationX(double angle);
Matrix rotationY(double angle);
Matrix rotationZ(double angle);
Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy);

Matrix viewTransformation(const Tuple& from, const Tuple& to, const Tuple& up);