#include "Matrix.h"
namespace s21{
Matrix::Matrix() : _rows(1), _cols(1) { this->_matrix = New_matrix(1, 1); }

Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    if (this->_rows > 0 && this->_cols > 0) {
        this->_matrix = New_matrix(this->_rows, this->_cols);

    } else {
        this->_rows = this->_cols = 0;
        throw std::invalid_argument("Invalid size of matrix");
    }
}

Matrix::Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols) {
    this->CopyMatrix(other._matrix);
}

Matrix::Matrix(Matrix&& other) : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
    other._cols = 0;
    other._rows = 0;
    other._matrix = nullptr;
}

Matrix::~Matrix() {
    if (_cols > 0 && _rows > 0) {
        this->Free_matrix();
    }
}

double** Matrix::New_matrix(int rows, int cols) {
    double** _matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        _matrix[i] = new double[cols]();
    }
    return _matrix;
}

void Matrix::Free_matrix() {
    for (int i = 0; i < _rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

void Matrix::CopyMatrix(double** matrix_copy) {
    this->_matrix = New_matrix(this->_rows, this->_cols);
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            this->_matrix[i][j] = matrix_copy[i][j];
        }
    }
}

bool Matrix::eq_matrix(const Matrix& other) const {
    bool ret_val = true;
    if (_cols == other._cols && _rows == other._rows) {
        for (int i = 0; i < _rows && ret_val == true; i++) {
            for (int j = 0; j < _cols && ret_val == true; j++) {
                if (fabs(other._matrix[i][j] - this->_matrix[i][j]) > 1e-6) {
                    ret_val = false;
                }
            }
        }
    } else {
        ret_val = false;
    }
    return ret_val;
}

bool Matrix::operator==(const Matrix& other) const { return eq_matrix(other); }

void Matrix::sum_matrix(const Matrix& other) {
    bool ret_val = true;
    if (this->_cols == other._cols && this->_rows == other._rows) {
        for (int i = 0; i < _rows && ret_val == true; i++) {
            for (int j = 0; j < _cols && ret_val == true; j++) {
                _matrix[i][j] += other._matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Matrices are not the same size");
    }
}

Matrix Matrix::operator+(const Matrix& other) {
    Matrix result = *this;
    result.sum_matrix(other);
    return result;
}

Matrix Matrix::operator+=(const Matrix& other) {
    this->sum_matrix(other);
    return (*this);
}
//    Sub matrix
void Matrix::sub_matrix(const Matrix& other) {
    bool ret_val = true;
    if (_rows == other._rows && _cols == other._cols) {
        for (int i = 0; i < _rows && ret_val == true; i++) {
            for (int j = 0; j < _cols && ret_val == true; j++) {
                _matrix[i][j] -= other._matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Matrices are not the same size");
    }
}

Matrix Matrix::operator-(const Matrix& other) {
    Matrix result = *this;
    result.sub_matrix(other);
    return result;
}

Matrix Matrix::operator-=(const Matrix& other) {
    this->sub_matrix(other);
    return (*this);
}

void Matrix::mul_matrix(const Matrix& other) {
    if (this->_cols == other._rows) {
        Matrix result(this->_rows, other._cols);
        for (int i = 0; i < this->_rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int k = 0; k < other._rows; k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        *this = result;
    } else {
        throw std::invalid_argument("Matrix size error");
    }
}

void Matrix::mul_number(const double num) {
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            (*this)(i, j) *= num;
        }
    }
}

Matrix operator*(const Matrix& other, double const num) {
    Matrix result = other;
    result.mul_number(num);
    return result;
}

Matrix operator*(double const num, const Matrix& other) {
    Matrix result = other;
    result.mul_number(num);
    return result;
}

Matrix Matrix::operator*(const Matrix& A) {
    Matrix result(*this);
    result.mul_matrix(A);
    return result;
}

Matrix Matrix::operator*=(const Matrix& other) {
    this->mul_matrix(other);
    return (*this);
}

Matrix Matrix::operator*=(const double num) {
    this->mul_number(num);
    return (*this);
}

Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        this->Free_matrix();
        this->_rows = other._rows;
        this->_cols = other._cols;
        this->CopyMatrix(other._matrix);
    }
    return *this;
}

double& Matrix::operator()(int i, int j) const {
    if (i < this->_rows && i >= 0 && j < this->_cols && j >= 0) {
        return (this->_matrix[i][j]);
    } else {
        throw std::out_of_range("index matrix error");
    }
}

Matrix Matrix::transpose() {
    Matrix result(this->_cols, this->_rows);
    for (int i = 0; i < result._rows; i++) {
        for (int j = 0; j < result._cols; j++) {
            result(i, j) = this->_matrix[j][i];
        }
    }
    return result;
}

Matrix Matrix::create_minor(int row, int column) {
    Matrix minor(this->_rows - 1, this->_cols - 1);
    int flag_row = 0;
    for (int i = 0; i < this->_rows; i++) {
        int flag_column = 0;
        if (i != row) {
            for (int j = 0; j < this->_cols; j++) {
                if (j != column) {
                    minor(i - flag_row, j - flag_column) = (*this)(i, j);
                } else {
                    flag_column = 1;
                }
            }
        } else {
            flag_row = 1;
        }
    }
    return minor;
}

double Matrix::determinant() {
    if (this->_rows == this->_cols) {
        double result = 0.0;
        if (this->_cols != 1) {
            for (int i = 0; i < this->_cols; i++) {
                Matrix minor = this->create_minor(0, i);
                if (i % 2 == 0) {
                    result += minor.determinant() * (*this)(0, i);
                } else {
                    result -= minor.determinant() * (*this)(0, i);
                }
            }
        } else {
            result = (*this)(0, 0);
        }
        return result;
    } else {
        throw std::invalid_argument("This matrix is not square");
    }
}

Matrix Matrix::calc_complements() {
    if (this->_cols == this->_rows && this->_rows > 1) {
        Matrix result(this->_rows, this->_cols);
        for (int i = 0; i < this->_rows; i++) {
            for (int j = 0; j < this->_cols; j++) {
                Matrix minor = this->create_minor(i, j);
                if ((i + j) % 2 == 0) {
                    result(i, j) = minor.determinant();
                } else {
                    result(i, j) = -minor.determinant();
                }
            }
        }
        return result;
    } else {
        throw std::invalid_argument("Matrix is not square or size <=1");
    }
}

Matrix Matrix::inverse_matrix() {
    if (fabs(this->determinant()) > 1e-6) {
        Matrix result(1, 1);
        if (_rows > 1) {
            Matrix comp = calc_complements();
            Matrix cont_trans = comp.transpose();
            cont_trans.mul_number(1.0 / determinant());
            result = cont_trans;
        } else {
            result._matrix[0][0] = 1.0 / _matrix[0][0];
        }
        return result;
    } else {
        throw std::invalid_argument("Matrix determinant equals zero");
    }
}
// Accessors & mutators
int Matrix::getRows() { return this->_rows; }

int Matrix::getCols() { return this->_cols; }
void Matrix::setRandom(){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            _matrix[i][j]=(std::rand()%10000+1.0)/10000.0;
        }
    }
}

void Matrix::setValueForAll(double value){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            _matrix[i][j]=value;
        }
    }
}

void Matrix::print(){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            std::cout<< _matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
}    //    namespace s21
