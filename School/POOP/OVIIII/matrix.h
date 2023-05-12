#pragma once
#include <iostream>
#include <utility>

class Matrix {
private:
    int rows;
    int columns;
    double** matrix;
public:
    Matrix(int nRows, int nColumns);
    explicit Matrix(int nRows);
    ~Matrix();
    
    double get(int row, int col) const;
    void set(int row, int col, double value);

    double *operator[](int row);                    //Valgfri oppgave

    int getRows() const {return rows;};
    int getColumns() const {return columns;};

    Matrix(const Matrix & rhs);

    Matrix& operator=(Matrix rhs);
    Matrix& operator+=(const Matrix & rhs);
    Matrix operator+(const Matrix & rhs) const;

    Matrix& operator-=(const Matrix & rhs);         //Valgfri oppgave
    Matrix operator-(const Matrix & rhs) const;     //Valgfri oppgave

    Matrix operator*(const Matrix & rhs) const;     //Valgfri oppgave
    Matrix& operator*=(const Matrix & rhs);         //Valgfri oppgave
    Matrix operator*(double rhs) const;             //Valgfri oppgave
    Matrix& operator*=(double rhs);                 //Valgfri oppgave

    Matrix operator-() const;                       //Valgfri oppgave
};

std::ostream &operator<<(std::ostream &os, const Matrix &rhs);

void testMatrix();

Matrix operator*(double lhs, const Matrix & rhs);   //Valgfri oppgave

void testMatrixExtra();                             //Valgfri oppgave