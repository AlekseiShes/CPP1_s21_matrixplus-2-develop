#ifndef S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define S21_MATRIXPLUS_S21_MATRIX_OOP_H_

// ****************************************
/*
Number of line - FUNCTION NAME
  6 - Destructor
 23 - Constructor (Empty)
 25 - Constructor (With arguments)
 47 - Copy constructor
 8o - Copy assignment operator =
 91 - Move constructor
1o7 - Move assignment operator =
115 - EqMatrix
127 - SumMatrix
132 - SubMatrix
137 - MulNumber
142 - MulMatrix
189 - Transpose
2o5 - CalcComplements
225 - Determinant
245 - InverseMatrix
      Operators
269 - +
275 - -
281 - *
3o1 - ==
295 - +=
3o8 - -=
313 - *=
324 - ()
352 - getRows getCols

*/
// ****************************************

#include <cmath>
#include <iostream>

//#include "string.h"
#define PRECISION 1e-07

namespace ns_21_Matrix {
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // service
  void setValue(int row, int col, double val);
  double getValue(int row, int col);
  int getRows() const noexcept;
  int getCols() const noexcept;
  void setRows(int rows);
  void setCols(int cols);

  // operators
  double &operator()(int i, int j);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  friend S21Matrix operator*(const double &num, const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);

  // Additional
  S21Matrix operator/(const double num);
  S21Matrix operator/=(const double num);
  S21Matrix operator/=(const S21Matrix &other);
  S21Matrix operator/(const S21Matrix &other);
  friend S21Matrix operator/(const double &num, const S21Matrix &other);

 private:
  int rows_{0}, cols_{0};
  double **matrix_{nullptr};

  void Reset();
  void Delete();
  void Create(int rows, int cols);
  void moveM(const S21Matrix &other);
  bool IsCorrect() const;
  bool IsEqualSize(const S21Matrix &other);
  void CheckInRange(int i, int max, const char *name);
  void CheckIndexes(int row, int col);
  void Linear_Arithmetic(double num, const S21Matrix *other);
  void fillMinor(const S21Matrix &other, int row, int col);

  // Additional
  void DivNumber(const double num);
};
S21Matrix operator*(const double &num, const S21Matrix &other);
// Additional
S21Matrix operator/(const double &num, const S21Matrix &other);
}  // namespace ns_21_Matrix

#endif  //  S21_MATRIXPLUS_S21_MATRIX_OOP_H_
