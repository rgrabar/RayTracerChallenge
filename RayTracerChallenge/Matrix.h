#pragma once

#include "Tuple.h"
#include <stdlib.h>     /* malloc, calloc, realloc, free */
#include <memory>
#include "Arena.h"

class Matrix {

public:

	Matrix(int _h, int _w);
	~Matrix();
	int h, w;
	double* matrix;
	// arena code
	//static struct Arena a;
	Matrix& operator=(const Matrix& matrix);
	
	void setElement(int y, int x, double value);
	const Matrix transpose()const;
	const double determinant()const;
	Matrix submatrix(int row, int col)const;
	const double minor(int row, int col)const;
	const double cofactor(int row, int col)const;
	const double invertible()const;
	Matrix* inverse();

	Matrix* cachedMatrix = nullptr;

};

// TODO: not sure if this is the best to use identity matrix function...
Matrix identityMatrix(int dimension);

bool operator==(const Matrix& lhs, const Matrix& rhs);
const Matrix operator*(const Matrix& lhs, const Matrix& rhs);
const Tuple operator*(const Matrix& lhs, const Tuple& rhs);