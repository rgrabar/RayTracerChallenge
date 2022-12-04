#include "Transformations.h"
#include <iostream>

Matrix translate(float x, float y, float z) {
	Matrix translation = Matrix(4, 4);
	for (int i = 0; i < translation.h; ++i) {
		for (int j = 0; j < translation.w; ++j) {
			if (i == j)
				translation.matrix[i * translation.w + j] = 1;
		}
	}
	translation.matrix[3] = x;
	translation.matrix[7] = y;
	translation.matrix[11] = z;

	return translation;
}

Matrix scale(float x, float y, float z) {
	Matrix scaled = Matrix(4, 4);
	for (int i = 0; i < scaled.h; ++i) {
		for (int j = 0; j < scaled.w; ++j) {
			if (i == j)
				scaled.matrix[i * scaled.w + j] = 1;
		}
	}
	scaled.matrix[0] = x;
	scaled.matrix[5] = y;
	scaled.matrix[10] = z;
	scaled.matrix[15] = 1;

	return scaled;
}

Matrix rotationX(float angle) {

	Matrix rotationX = Matrix(4, 4);
	float cosR = cos(angle);
	float sinR = sin(angle);

	rotationX.matrix[0] = 1;
	rotationX.matrix[5] = cosR;
	rotationX.matrix[6] = -sinR;
	rotationX.matrix[9] = sinR;
	rotationX.matrix[10] = cosR;
	rotationX.matrix[15] = 1;

	return rotationX;
}

Matrix rotationY(float angle) {

	Matrix rotationY = Matrix(4, 4);
	float cosR = cos(angle);
	float sinR = sin(angle);

	rotationY.matrix[0] = cosR;
	rotationY.matrix[2] = sinR;
	rotationY.matrix[5] = 1;
	rotationY.matrix[8] = -sinR;
	rotationY.matrix[10] = cosR;
	rotationY.matrix[15] = 1;

	return rotationY;
}

Matrix rotationZ(float angle) {

	Matrix rotationZ = Matrix(4, 4);
	float cosR = cos(angle);
	float sinR = sin(angle);

	rotationZ.matrix[0] = cosR;
	rotationZ.matrix[1] = -sinR;
	rotationZ.matrix[4] = sinR;
	rotationZ.matrix[5] = cosR;
	rotationZ.matrix[10] = 1;
	rotationZ.matrix[15] = 1;

	return rotationZ;
}

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy) {

	Matrix shear = Matrix(4, 4);
	shear.matrix[0] = 1;
	shear.matrix[1] = xy;
	shear.matrix[2] = xz;
	shear.matrix[4] = yx;
	shear.matrix[5] = 1;
	shear.matrix[6] = yz;
	shear.matrix[8] = zx;
	shear.matrix[9] = zy;
	shear.matrix[10] = 1;
	shear.matrix[15] = 1;

	return shear;
}