#include "Matrix.h"
#include "Helper.h"
#include <iostream>
#include <vector>
#include <ppl.h>

using namespace concurrency;

// arena code
//Arena Matrix::a {0};

Matrix::Matrix(int _h, int _w) : h(_h), w(_w) {
    /*
    // arena code
    if (a.buf == nullptr) {
        //std::cout << "NULLPRT\n";
        //1002640576
        void* backing_buffer = malloc(100024 * 100024);
        arena_init(&a, backing_buffer, 100024 * 100024);
    }
   
    matrix = (double*)arena_alloc(&a, w * h * sizeof(double));
    */

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

Matrix::~Matrix() {
    // remove for arena
    free(matrix);
    free(aaa);
}

Matrix::Matrix(const Matrix& matrix) {
    this->w = matrix.w;
    this->h = matrix.h;

    this->matrix = (double*)malloc(w * h * sizeof(double));
    memcpy(this->matrix, matrix.matrix, w * h * sizeof(double));
}

void Matrix::setElement(int y, int x, double value) {
    matrix[y * w + x] = value;
}

const Matrix Matrix::transpose() const {
    Matrix transposed(w, h);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            transposed.matrix[i * w + j] = matrix[j * w + i];
        }
    }
    return transposed;
}

const double Matrix::determinant()const {
    if(w == 2)
        return matrix[0] * matrix[3] - matrix[1] * matrix[2];
    double det = 0;
    for (int i = 0; i < w; ++i) {
        det += matrix[i] * cofactor(0, i);
    }
    return det;
}

const double Matrix::minor(int row, int col)const {
    return submatrix(row, col).determinant();
}

const double Matrix::cofactor(int row, int col)const {
    if ((row + col) % 2 == 0) {
        return minor(row, col);
    }
    return minor(row, col) * -1;
}

const double Matrix::invertible()const {
    return determinant() != 0;
}

Matrix* Matrix::inverse() {
    // TODO: return some error?
    if (!invertible()) {
        std::cout << "Not invertible!\n";
    }

    if (aaa == nullptr) {

        aaa = new Matrix(w, h);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; ++j) {
                double c = cofactor(i, j);
                aaa->matrix[j * w + i] = c / determinant();
            }
        }
        return aaa;

    }
    return aaa;
}

Matrix Matrix::submatrix(int row, int col)const {
    Matrix sub(w - 1, h - 1);
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

    //TODO: almost no impact?
    parallel_for(0, lhs.h, [&](size_t row) {
        for (int col = 0; col < rhs.w; ++col) {
            double element = 0;
            for (int i = 0; i < lhs.w; ++i) {
                element += lhs.matrix[row * lhs.w + i] * rhs.matrix[i * rhs.w + col];
            }
            ret.matrix[row * rhs.w + col] = element;
        }
    });

    return ret;
}

const Tuple operator*(const Matrix& lhs, const Tuple& rhs) {
    return Tuple(
        //m(0, 0) * t.x() + m(0, 1) * t.y() + m(0, 2) * t.z() + m(0, 3) * t.w(),
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