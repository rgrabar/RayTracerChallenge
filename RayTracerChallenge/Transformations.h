#pragma once
#include "Matrix.h"
#include <math.h>

Matrix translate(float x, float y, float z);
Matrix scale(float x, float y, float z);
// angle is in radians
Matrix rotationX(float angle);
Matrix rotationY(float angle);
Matrix rotationZ(float angle);
Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

Matrix viewTransformation(const Tuple& from, Tuple& to, Tuple&up);