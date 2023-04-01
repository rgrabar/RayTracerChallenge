#pragma once

#include "Tuple.h"
#include <stdlib.h>     /* malloc, calloc, realloc, free */
#include <memory>

class Matrix {

public:

	Matrix(int _h, int _w);
	Matrix(Matrix& other);
	
	~Matrix();
	int h, w;
	double* matrix;
	Matrix& operator=(const Matrix& matrix);
	
	void setElement(int y, int x, double value);
	Matrix transpose()const;
	double determinant()const;
	Matrix submatrix(int row, int col)const;
	double minor(int row, int col)const;
	double cofactor(int row, int col)const;
	double invertible()const;
	Matrix* inverse();

	Matrix* cachedMatrix = nullptr;

};

// TODO: not sure if this is the best to use identity matrix function...
Matrix identityMatrix(int dimension);

bool operator==(const Matrix& lhs, const Matrix& rhs);
const Matrix operator*(const Matrix& lhs, const Matrix& rhs);
const Tuple operator*(const Matrix& lhs, const Tuple& rhs);