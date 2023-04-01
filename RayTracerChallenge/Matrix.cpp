#include "Matrix.h"
#include "Helper.h"
#include <cstring>
#include <iostream>
#include <vector>

Matrix::Matrix(int _h, int _w) : h(_h), w(_w) {
    matrix = (double*)calloc(h * w, sizeof(double));
    if (matrix) {
        //std::cout << "allocated\n";
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                matrix[i * w + j] = 0.0;
            }
        }
    }
    else {
        std::cout << "Can't allocate memory for the matrix!";
    }
};

Matrix::Matrix(Matrix& other) {
    h = other.h;
    w = other.w;

    matrix = (double*)malloc(w * h * sizeof(double));
    memcpy(matrix, other.matrix, w * h * sizeof(double));
 
    cachedMatrix = other.cachedMatrix;
};


Matrix::~Matrix() {
    free(matrix);
    if(cachedMatrix != nullptr)
        delete(cachedMatrix);
}

void Matrix::setElement(int y, int x, double value) {
    matrix[y * w + x] = value;
}

Matrix Matrix::transpose() const {
    Matrix transposed(w, h);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            transposed.matrix[i * w + j] = matrix[j * w + i];
        }
    }
    return transposed;
}

double Matrix::determinant()const {
    if(w == 2)
        return matrix[0] * matrix[3] - matrix[1] * matrix[2];
    double det = 0;
    for (int i = 0; i < w; ++i) {
        det += matrix[i] * cofactor(0, i);
    }
    return det;
}

double Matrix::minor(int row, int col)const {
    return submatrix(row, col).determinant();
}

double Matrix::cofactor(int row, int col)const {
    if ((row + col) % 2 == 0) {
        return minor(row, col);
    }
    return minor(row, col) * -1;
}

double Matrix::invertible()const {
    return determinant() != 0;
}

Matrix* Matrix::inverse() {
    // TODO: return some error?

    if (!invertible()) {
        std::cout << "Not invertible!\n";
    }

    if (cachedMatrix == nullptr) {

        cachedMatrix = new Matrix(w, h);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; ++j) {
                double c = cofactor(i, j);
                cachedMatrix->matrix[j * w + i] = c / determinant();
            }
        }
        return cachedMatrix;

    }
    return cachedMatrix;
}

Matrix Matrix::submatrix(int row, int col)const {
    Matrix sub(h - 1, w - 1);
    int tmp = 0 , tmp1 = 0;
    for (int i = 0; i < h; ++i) {
        if (i == row)
            continue;
        tmp = 0;
        for (int j = 0; j < w; ++j) {
            if (j == col)
                continue;
            sub.matrix[tmp1 * (w  - 1) + tmp] = matrix[i * w + j];
            tmp++;
        }
        tmp1++;
    }
    return sub;
}

Matrix& Matrix::operator=(const Matrix &matrix) {
    if (this != &matrix) {
        if (w == matrix.w && h == matrix.h) {
            memcpy(this->matrix, matrix.matrix, this->w * this->h * sizeof(double));
        }
        else {
            w = matrix.w;
            h = matrix.h;
            free(this->matrix);
            this->matrix = (double*)malloc(this->w * this->h * sizeof(double));
            memcpy(this->matrix, matrix.matrix, w * h * sizeof(double));
        }
    }

    return *this;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.w != rhs.w || lhs.h != rhs.h) {
        return false;
    }
    for (int row = 0; row < lhs.h; ++row) {
        for (int col = 0; col < lhs.w; ++col) {
            if (!epsilonEqual(lhs.matrix[row * lhs.w + col], rhs.matrix[row * rhs.w + col])) {
                return false;
            }
        }
    }
    return true;
}

const Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    Matrix ret = Matrix(lhs.h, rhs.w);

    for (int row = 0; row < lhs.h; ++row) {
        for (int col = 0; col < rhs.w; ++col) {
            double element = 0;
            for (int i = 0; i < lhs.w; ++i) {
                element += lhs.matrix[row * lhs.w + i] * rhs.matrix[i * rhs.w + col];
            }
            ret.matrix[row * rhs.w + col] = element;
        }
    }

    return ret;
}

const Tuple operator*(const Matrix& lhs, const Tuple& rhs) {
    return Tuple(
        lhs.matrix[0] * rhs.x + lhs.matrix[1] * rhs.y + lhs.matrix[2] * rhs.z + lhs.matrix[3] * rhs.w,
        lhs.matrix[4] * rhs.x + lhs.matrix[5] * rhs.y + lhs.matrix[6] * rhs.z + lhs.matrix[7] * rhs.w,
        lhs.matrix[8] * rhs.x + lhs.matrix[9] * rhs.y + lhs.matrix[10] * rhs.z + lhs.matrix[11] * rhs.w,
        lhs.matrix[12] * rhs.x + lhs.matrix[13] * rhs.y + lhs.matrix[14] * rhs.z + lhs.matrix[15] * rhs.w
    );
}


Matrix identityMatrix(int dimension) {
    Matrix identity = Matrix(dimension, dimension);
    for (int i = 0; i < dimension; ++i) {
        identity.setElement(i, i, 1);
    }
    return identity;
}