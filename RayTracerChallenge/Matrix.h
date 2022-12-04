#pragma once

#include "Tuple.h"

class Matrix {

public:

	Matrix(int _h, int _w);
	int h, w;
	float* matrix;

	void setElement(int y, int x, float value);
	const Matrix transpose()const;
	const float determinant()const;
	Matrix submatrix(int row, int col)const;
	const float minor(int row, int col)const;
	const float cofactor(int row, int col)const;
	const float invertible()const;
	const Matrix inverse()const;

};

// TODO: not sure if this is the best to use identity matrix function...
Matrix identityMatrix(int dimension);

bool operator==(const Matrix lhs, const Matrix rhs);
const Matrix operator*(const Matrix lhs, const Matrix rhs);
const Tuple operator*(const Matrix lhs, const Tuple rhs);