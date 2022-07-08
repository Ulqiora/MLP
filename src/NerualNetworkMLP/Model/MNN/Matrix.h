#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <iostream>
#include <vector>
#include "../constantValues.h"
#include "../Dataset.h"
namespace s21{
class Matrix {
    friend Matrix operator*(const Matrix& other, double const num);
    friend Matrix operator*(double const num, const Matrix& other);

 private:
    int _rows, _cols;
    double** _matrix;
    double** New_matrix(int rows, int cols);
    void Free_matrix();
    void CopyMatrix(double** matrix_copy);
    Matrix create_minor(int row, int column);

 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Image& pixels);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    Matrix operator=(const Matrix& other);

    bool eq_matrix(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    // sum
    void sum_matrix(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator+=(const Matrix& other);
    // sub
    void sub_matrix(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    // mul
    void mul_number(const double num);
    void mul_matrix(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*=(const Matrix& other);
    Matrix operator*=(const double num);
    // operation
    Matrix transpose();
    Matrix calc_complements();
    double determinant();
    Matrix inverse_matrix();

    double operator()(int i, int j) const;
    void setValue(int i, int j,double value);
    // other
    int getRows()const;
    int getCols()const;
    void setRandom();
    void setValueForAll(double value);
    void print()const;
};
}

#endif // MATRIX_H
