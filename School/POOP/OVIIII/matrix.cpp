#include "matrix.h"
#include <cassert>

Matrix::Matrix(int nRows, int nColumns) : rows{nRows}, columns{nColumns} {
    assert(rows >= 1);
    assert(columns >= 1);
    matrix = new double*[rows];
    for (int row = 0; row<rows; row++){
        matrix[row] = new double[columns];
        for (int col = 0; col<columns; col++) {
            matrix[row][col] = 0.0;
        }
    }
}

Matrix::Matrix(int nRows): Matrix(nRows, nRows) {
    for (int row = 0; row<rows; row++) {
        matrix[row][row] = 1.0;
    }
}

Matrix::~Matrix() {
    for (int row = 0; row<rows; row++){
        delete[] matrix[row];
        matrix[row] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;

    rows = 0;
    columns = 0;
}

double Matrix::get(int row, int col) const{
    return matrix[row][col];
}

void Matrix::set(int row, int col, double value) {
    matrix[row][col] = value;
}

double *Matrix::operator[](int row){ // Valgfri oppgave
    assert(row >= 0 && row < rows);
    return matrix[row];
}

std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {
    for (int row = 0; row<rhs.getRows(); row++){
        for (int col = 0; col<rhs.getColumns(); col++) {
            os << rhs.get(row,col) << '\t';
        }
        os << '\n';
    }
    return os;
}

Matrix::Matrix(const Matrix & rhs) : Matrix(rhs.getRows(), rhs.getColumns()) {
    for (int row = 0; row<rows; row++){
        for (int col = 0; col<columns; col++) {
            matrix[row][col] = rhs.get(row,col);
        }
    }
}

Matrix& Matrix::operator=(Matrix rhs) {
    std::swap(this->rows, rhs.rows);
    std::swap(this->columns, rhs.columns);
    std::swap(this->matrix, rhs.matrix);

    return *this;
}

Matrix& Matrix::operator+=(const Matrix & rhs) {
    assert(this->getRows() == rhs.getRows() && this->getColumns() == rhs.getColumns());
    for (int row = 0; row<this->rows; row++){
        for (int col = 0; col<this->columns; col++) {
            this->matrix[row][col] = this->matrix[row][col] + rhs.matrix[row][col];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix & rhs) const {
    assert(this->getRows() == rhs.getRows() && this->getColumns() == rhs.getColumns());
    return Matrix{ *this } += rhs;
}

void testMatrix() {
    Matrix A(2);
    Matrix B(2);
    Matrix C(2);

    A.set(0,0,1.0);
    A.set(0,1,2.0);
    A.set(1,0,3.0);
    A.set(1,1,4.0);

    B.set(0,0,4.0);
    B.set(0,1,3.0);
    B.set(1,0,2.0);
    B.set(1,1,1.0);

    C.set(0,0,1.0);
    C.set(0,1,3.0);
    C.set(1,0,1.5);
    C.set(1,1,2.0);

    std::cout << "A:\n" << A << '\n'
              << "B:\n" << B << '\n'
              << "C:\n" << C << '\n';

    std::cout << "After A += B + C\n";

    A += B + C;

    std::cout << "A:\n" << A << '\n'
              << "B:\n" << B << '\n'
              << "C:\n" << C << '\n';
}

Matrix& Matrix::operator-=(const Matrix & rhs){ //Valgfri oppgave
    assert(this->getRows() == rhs.getRows() && this->getColumns() == rhs.getColumns());
    for (int row = 0; row<this->rows; row++){
        for (int col = 0; col<this->columns; col++) {
            this->matrix[row][col] = this->matrix[row][col] - rhs.matrix[row][col];
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix & rhs) const { //Valgfri oppgave
    assert(this->getRows() == rhs.getRows() && this->getColumns() == rhs.getColumns());
    return Matrix{ *this } -= rhs;
}

Matrix Matrix::operator*(const Matrix & rhs) const { //Valgfri oppgave
    assert(this->getColumns() == rhs.getRows());

    Matrix result{this->getRows(),rhs.getColumns()};
    for (int row = 0; row < this->getRows(); row++){
        for (int col = 0; col < rhs.getColumns(); col++){
            for (int i = 0; i< this->getColumns(); i++){
                result[row][col] += this->get(row, i) * rhs.get(i,col);
            }
        }
    }

    return result;
}

Matrix& Matrix::operator*=(const Matrix & rhs) { //Valgfri oppgave
    return *this = *this * rhs;
}

Matrix Matrix::operator*(double rhs) const{ //Valgfri oppgave
    for (int row = 0; row<this->rows; row++){
        for (int col = 0; col<this->columns; col++) {
            this->matrix[row][col] = this->matrix[row][col] * rhs;
        }
    }
    return *this;
}

Matrix operator*(double lhs, const Matrix & rhs){ //Valgfri oppgave
    return rhs * lhs;
}

Matrix& Matrix::operator*=(double rhs){ //Valgfri oppgave
    return *this = *this * rhs;
}

Matrix Matrix::operator-() const{ //Valgfri oppgave
    return *this * -1.0;
}

void testMatrixExtra(){ //Valgfri oppgave test-funksjon
    Matrix A(2);
    Matrix B(2);
    Matrix C(2);

    A.set(0,0,1.0);
    A.set(0,1,2.0);
    A.set(1,0,3.0);
    A.set(1,1,4.0);

    B.set(0,0,4.0);
    B.set(0,1,3.0);
    B.set(1,0,2.0);
    B.set(1,1,1.0);

    C.set(0,0,1.0);
    C.set(0,1,3.0);
    C.set(1,0,1.5);
    C.set(1,1,2.0);

    Matrix D = A*B-C;

    A = -A;
    B *= B;
    C *= 5;

    std::cout << "-A:\n" << A << '\n'
              << "B*B:\n" << B << '\n'
              << "C*5:\n" << C << '\n'
              << "D = A*B-C\n" << D << '\n';
}