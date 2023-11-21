#include <gtest/gtest.h>
// To get GoogleTest you shoud intype in terminal:
// sudo apt update
// sudo apt install libgtest-dev

#include <stdlib.h>
#include <time.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "s21_matrix_oop.h"

using namespace std;

using namespace ns_21_Matrix;
int WITH_THROW = 1;

enum FillRegim { byZero = 0, byOne = 1, byIndex, byDiag, byRand };

void FillMatrixValue(FillRegim regim, S21Matrix* matrix) {
  for (int i = 0; i < matrix->getRows(); ++i)
    for (int j = 0; j < matrix->getCols(); ++j) switch (regim) {
        case byOne:
          matrix->setValue(i, j, 1);
          break;
        case byIndex:
          matrix->setValue(i, j, i + j + 1);
          break;
        case byDiag:
          matrix->setValue(i, j, i == j);
          break;
        case byRand:
          matrix->setValue(i, j, 0.01 * (5000 - std::rand() % 10000));
          break;
        default:
          matrix->setValue(i, j, 0);
          break;
      }
}

TEST(Declaration, PositiveTest_1) {
  S21Matrix matrix_1;
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
}

TEST(Constructor, PositiveTest_2) {
  S21Matrix matrix_1 = S21Matrix(2, 3);
  EXPECT_EQ(matrix_1.getRows(), 2);
  EXPECT_EQ(matrix_1.getCols(), 3);
}

TEST(Constructor, NegativeTest) {
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_ANY_THROW(S21Matrix matrix_1(3, -1));
    EXPECT_ANY_THROW(S21Matrix matrix_1(0, 5));
  }
}

TEST(CopyConstructor_Eq, PositiveTest_Empty) {
  S21Matrix matrix_1;
  S21Matrix matrix_2(matrix_1);
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
  EXPECT_EQ(matrix_2.getRows(), 0);
  EXPECT_EQ(matrix_2.getCols(), 0);
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_1));
}

TEST(CopyConstructor_Eq, PositiveTest_Zere) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(matrix_1);

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_EQ(matrix_2.getRows(), rows);
  EXPECT_EQ(matrix_2.getCols(), cols);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(CopyConstructor_Eq, PositiveTest_Rand) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  FillMatrixValue(byRand, &matrix_1);

  S21Matrix matrix_2(matrix_1);

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_EQ(matrix_2.getRows(), rows);
  EXPECT_EQ(matrix_2.getCols(), cols);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(CopyConstructor_Eq, PositiveTest_Rand_Tern) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  FillMatrixValue(byRand, &matrix_1);

  S21Matrix matrix_2 = matrix_1;

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_EQ(matrix_2.getRows(), rows);
  EXPECT_EQ(matrix_2.getCols(), cols);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(CopyConstructor_Eq, NegativeTest_Rand) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  FillMatrixValue(byRand, &matrix_1);

  S21Matrix matrix_2(matrix_1);

  for (int i = 0; i < matrix_1.getRows(); ++i)
    for (int j = 0; j < matrix_1.getCols(); ++j)
      matrix_1.setValue(i, j, matrix_1.getValue(i, j) + 1);

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_EQ(matrix_2.getRows(), rows);
  EXPECT_EQ(matrix_2.getCols(), cols);
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
}

TEST(EqMatrix, NegativeTest_DifSize) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  FillMatrixValue(byRand, &matrix_1);

  S21Matrix matrix_2(rows + 1 + std::rand() % 4, cols + 1 + std::rand() % 4);
  for (int i = 0; i < matrix_1.getRows(); ++i)
    for (int j = 0; j < matrix_1.getCols(); ++j)
      matrix_2.setValue(i, j, matrix_1.getValue(i, j));

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
}

TEST(EqMatrix, NegativeTest_DifSize_Tern) {
  int rows = 4, cols = 3;
  S21Matrix matrix_1(rows, cols);
  FillMatrixValue(byRand, &matrix_1);

  S21Matrix matrix_2(rows + 1 + std::rand() % 4, cols + 1 + std::rand() % 4);
  for (int i = 0; i < matrix_1.getRows(); ++i)
    for (int j = 0; j < matrix_1.getCols(); ++j)
      matrix_2.setValue(i, j, matrix_1.getValue(i, j));

  EXPECT_EQ(matrix_1.getRows(), rows);
  EXPECT_EQ(matrix_1.getCols(), cols);
  EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(MoveAndCopyAndEq, MixTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  FillMatrixValue(byRand, &matrix_1);
  S21Matrix matrix_2(matrix_1);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
  S21Matrix matrix_3(std::move(matrix_1));

  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_3));
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_3));
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
  EXPECT_EQ(matrix_2.getRows(), row);
  EXPECT_EQ(matrix_2.getCols(), col);
  EXPECT_EQ(matrix_3.getRows(), row);
  EXPECT_EQ(matrix_3.getCols(), col);
}

TEST(MoveConstructor, Replace) {
  int row, col;
  row = 3 + std::rand() % 5;
  col = 3 + std::rand() % 5;
  S21Matrix matrix_1(row, col);
  FillMatrixValue(byOne, &matrix_1);
  S21Matrix matrix_2(matrix_1);
  S21Matrix matrix_3(2, 2);
  FillMatrixValue(byOne, &matrix_3);
  matrix_3 *= 3;
  S21Matrix matrix_4(matrix_2);

  matrix_2 = (std::move(matrix_3));
  matrix_3 = (std::move(matrix_1));

  EXPECT_EQ(1, 1);
  EXPECT_FALSE(matrix_4.EqMatrix(matrix_2));
  EXPECT_TRUE(matrix_4.EqMatrix(matrix_3));
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_3));
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_4));
  EXPECT_EQ(matrix_2.getRows(), 2);
  EXPECT_EQ(matrix_2.getCols(), 2);
  EXPECT_EQ(matrix_3.getRows(), row);
  EXPECT_EQ(matrix_3.getCols(), col);
  EXPECT_EQ(matrix_2(1, 1), 3);
  EXPECT_EQ(matrix_3(2, 2), 1);
  EXPECT_ANY_THROW(matrix_1(0, 0));
}

TEST(SumMatrix, trueTest0) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);

  matrix_1.SumMatrix(matrix_1);
  matrix_2.MulNumber(2);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SumMatrix, trueTest1) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  FillMatrixValue(byRand, &tmpMatrix);

  matrix_1.SumMatrix(tmpMatrix);
  matrix_2 = matrix_2 + tmpMatrix;

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SumMatrix, trueTest2) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  FillMatrixValue(byRand, &tmpMatrix);

  matrix_1.SumMatrix(tmpMatrix);
  matrix_2 += tmpMatrix;

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SumAndMultNumMatrix, trueTest_tern) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix1(row, col);
  S21Matrix tmpMatrix2(row, col);
  S21Matrix ResMatrix(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  FillMatrixValue(byRand, &tmpMatrix1);
  FillMatrixValue(byIndex, &ResMatrix);

  ResMatrix.MulNumber(2);
  tmpMatrix1 = matrix_1 + matrix_2 * 1;
  tmpMatrix2 = 2 * matrix_1;
  matrix_2 *= 2;

  EXPECT_FALSE(tmpMatrix1 == matrix_1);
  EXPECT_TRUE(ResMatrix == matrix_2);
  EXPECT_TRUE(ResMatrix == tmpMatrix1);
  EXPECT_TRUE(ResMatrix == tmpMatrix2);
  EXPECT_TRUE(tmpMatrix1 == tmpMatrix2);
}

TEST(SumMatrix, assertThrow) {
  S21Matrix matrix_1(5, 3);
  S21Matrix matrix_2(3, 4);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_ANY_THROW(matrix_1.SumMatrix(matrix_2));
  }
}

TEST(SubMatrix, trueTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  FillMatrixValue(byRand, &tmpMatrix);
  matrix_1.SubMatrix(tmpMatrix);
  matrix_2.SubMatrix(tmpMatrix);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SubMatrix, trueTest_tern) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix(row, col);
  S21Matrix ResMatrix(row, col);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  FillMatrixValue(byRand, &tmpMatrix);
  FillMatrixValue(byZero, &ResMatrix);

  tmpMatrix = matrix_1 - matrix_2;
  matrix_2 -= matrix_1;

  EXPECT_FALSE(tmpMatrix == matrix_1);
  EXPECT_TRUE(ResMatrix == tmpMatrix);
  EXPECT_TRUE(ResMatrix == matrix_2);
}

TEST(SubMatrix, assertThrow) {
  S21Matrix matrix_1(5, 3);
  S21Matrix matrix_2(3, 4);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byIndex, &matrix_2);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.SubMatrix(matrix_2), std::out_of_range);
  }
}

TEST(MulNumber_, intTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);
  S21Matrix tmpMatrix(row, col);

  FillMatrixValue(byOne, &matrix_1);
  FillMatrixValue(byOne, &matrix_2);
  FillMatrixValue(byZero, &tmpMatrix);

  int num = std::rand() % 4;
  for (int i = 0; i < num; ++i) tmpMatrix.SumMatrix(matrix_1);

  matrix_2.MulNumber(num);

  EXPECT_TRUE(tmpMatrix.EqMatrix(matrix_2));
}

TEST(MulNumber_, doubleTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  S21Matrix matrix_2(row, col);

  FillMatrixValue(byOne, &matrix_1);

  double num = (std::rand() % 10000) / 100;
  if (std::rand() % 2) num *= (-1);
  for (int i = 0; i < matrix_2.getRows(); ++i)
    for (int j = 0; j < matrix_2.getCols(); ++j)
      matrix_2.setValue(i, j, matrix_1.getValue(i, j) * num);

  matrix_1.MulNumber(num);

  EXPECT_TRUE(matrix_2.EqMatrix(matrix_1));
}

TEST(MulNumber_, emptyTest) {
  S21Matrix matrix_1;
  S21Matrix matrix_2;

  matrix_1.MulNumber(9);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(Get_Value, trueTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  EXPECT_TRUE(fabs(0 - matrix_1.getValue(0, 0)) < PRECISION);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.getValue(row, col), std::out_of_range);
    ASSERT_THROW(matrix_1.getValue(-1, col - 1), std::out_of_range);
    ASSERT_THROW(matrix_1.getValue(0, col), std::out_of_range);
  }
}

TEST(Get_Value, trueTest_tern) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  EXPECT_TRUE(fabs(0 - matrix_1(0, 0)) < PRECISION);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1(row, col), std::out_of_range);
    ASSERT_THROW(matrix_1(-1, col - 1), std::out_of_range);
    ASSERT_THROW(matrix_1(0, col), std::out_of_range);
  }
}

TEST(setRows_setCols, trueTest) {
  int row = 1 + std::rand() % 4, col = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, col);
  FillMatrixValue(byOne, &matrix_1);
  matrix_1.setRows(row + 2);
  matrix_1.setCols(col + 2);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.setCols(0), std::logic_error);
    ASSERT_THROW(matrix_1.setRows(0), std::logic_error);
  }
  EXPECT_EQ(matrix_1(0, 0), 1);
  EXPECT_EQ(matrix_1(row, col), 0);
  EXPECT_EQ(matrix_1.getRows(), row + 2);
  EXPECT_EQ(matrix_1.getCols(), col + 2);
  matrix_1.setRows(1);
  matrix_1.setCols(1);
  EXPECT_EQ(matrix_1.getRows(), 1);
  EXPECT_EQ(matrix_1.getCols(), 1);
  EXPECT_EQ(matrix_1(0, 0), 1);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1(row, col), std::out_of_range);
    ASSERT_THROW(matrix_1.setCols(-1), std::logic_error);
    ASSERT_THROW(matrix_1.setRows(-7), std::logic_error);
  }
}

TEST(setRows_setCols, fromZero) {
  S21Matrix matrix_1;
  matrix_1.setRows(2);
  matrix_1.setCols(2);
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
}

TEST(setRowsCols, trueTest) {
  S21Matrix matrix_1(3, 3);
  matrix_1.setRows(5);
  matrix_1.setCols(7);

  EXPECT_EQ(matrix_1.getRows(), 5);
  EXPECT_EQ(matrix_1.getCols(), 7);
  ASSERT_THROW(matrix_1.setRows(0), std::logic_error);
  ASSERT_THROW(matrix_1.setCols(0), std::logic_error);

  S21Matrix matrix_2;
  matrix_2.setRows(3);
  EXPECT_ANY_THROW(matrix_2(0, 0));
}

TEST(TransposeMatrix, trueTest) {
  S21Matrix matrix(4, 3);
  S21Matrix result(3, 4);

  FillMatrixValue(byOne, &matrix);
  FillMatrixValue(byOne, &result);
  matrix(1, 0) = 5;
  result(0, 1) = 5;
  matrix(1, 2) = -0.3;
  result(2, 1) = -0.3;
  matrix = matrix.Transpose();

  EXPECT_TRUE(matrix.EqMatrix(result));
}

TEST(TransposeMatrix, Empty_Test) {
  S21Matrix matrix;
  S21Matrix result = matrix.Transpose();
  EXPECT_TRUE(matrix.EqMatrix(result));
}

TEST(Determinant, RandDimTest) {
  int size = 3 + std::rand() % 3;
  S21Matrix matrix_1(size, size);
  FillMatrixValue(byIndex, &matrix_1);
  EXPECT_TRUE(fabs(matrix_1.Determinant() - 0) < PRECISION);
}

TEST(Determinant, oneDimTest) {
  S21Matrix matrix_1(1, 1);
  matrix_1(0, 0) = 1;
  EXPECT_TRUE(fabs(matrix_1.Determinant() - 1) < PRECISION);
}

TEST(Determinant, twoDimTest) {
  S21Matrix matrix_1(2, 2);
  matrix_1(1, 0) = 5;
  matrix_1(0, 1) = 1;
  EXPECT_TRUE(fabs(matrix_1.Determinant() - (-5)) < PRECISION);
}

TEST(Determinant, threeDimTest) {
  S21Matrix matrix_1(3, 3);
  matrix_1(2, 0) = 5;
  matrix_1(1, 1) = 1;
  matrix_1(0, 2) = -5;
  EXPECT_TRUE(fabs(matrix_1.Determinant() - 25) < PRECISION);
}

TEST(Determinant, assertThrow) {
  int row = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, row + 1 + std::rand() % 4);
  FillMatrixValue(byIndex, &matrix_1);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.Determinant(), std::logic_error);
  }
}

TEST(MulMatrix, assertThrow) {
  S21Matrix matrix_1(7, 10);
  S21Matrix matrix_2(3, 4);

  FillMatrixValue(byIndex, &matrix_1);
  FillMatrixValue(byDiag, &matrix_2);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.MulMatrix(matrix_2), std::logic_error);
    ASSERT_THROW(S21Matrix matrix_3 = matrix_1 * matrix_2, std::logic_error);
    ASSERT_THROW(matrix_1 *= matrix_2, std::logic_error);
  }
}

TEST(MulMatrix, DiagMatrixTest) {
  int row = 1 + std::rand() % 4;
  S21Matrix matrix_1(row, row);
  S21Matrix matrix_2(row, row);
  FillMatrixValue(byRand, &matrix_1);
  FillMatrixValue(byDiag, &matrix_2);
  S21Matrix matrix_3 = matrix_1 * matrix_2;
  matrix_1 *= matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_3));
}

TEST(CalcComplement, assertThrow) {
  S21Matrix matrix_1(3, 4);
  FillMatrixValue(byRand, &matrix_1);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.CalcComplements(), std::logic_error);
  }
}

TEST(CalcComplement, OneDimTest) {
  S21Matrix matrix_1(1, 1);
  FillMatrixValue(byDiag, &matrix_1);
  matrix_1 *= 5;
  S21Matrix matrix_2 = matrix_1.CalcComplements();
  EXPECT_TRUE(fabs(matrix_2(0, 0) - 1) < PRECISION);
}

TEST(CalcComplement, RandDimTest) {
  int row = 1 + std::rand() % 3;
  double randVal = (-5000 + std::rand() % 10000) / 100;
  if (fabs(randVal) < PRECISION) randVal = 5;
  S21Matrix matrix_1(row, row);
  FillMatrixValue(byDiag, &matrix_1);
  matrix_1 *= randVal;
  S21Matrix matrix_2 = matrix_1.CalcComplements();
  EXPECT_TRUE(fabs(matrix_2(0, 0) - pow(randVal, row - 1)) < PRECISION);
}

TEST(Inverse, NoSquerThrow) {
  S21Matrix matrix_1(2, 3);
  FillMatrixValue(byDiag, &matrix_1);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.InverseMatrix(), std::logic_error);
  }
}

TEST(Inverse, DetZeroThrow) {
  S21Matrix matrix_1(3, 3);
  FillMatrixValue(byOne, &matrix_1);
  if (!WITH_THROW) {
    EXPECT_EQ(1, 1);
  } else {
    ASSERT_THROW(matrix_1.InverseMatrix(), std::invalid_argument);
  }
}

TEST(Inverse, ofNumerical) {
  S21Matrix matrix_1(1, 1);
  FillMatrixValue(byOne, &matrix_1);
  double randVal = (-5000 + std::rand() % 10000) / 100;
  if (fabs(randVal) < PRECISION) randVal = 5;
  S21Matrix matrix_2 = matrix_1 * randVal;
  S21Matrix matrix_3 = matrix_1 * (1 / randVal);
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_3.InverseMatrix()));
}

TEST(Inverse, RandDim_E) {
  int row = 1 + std::rand() % 7;
  double randVal = (-50 + std::rand() % 100) / 10;
  if (fabs(randVal) < PRECISION) randVal = 5;

  S21Matrix matrix_1(row, row);
  FillMatrixValue(byDiag, &matrix_1);
  S21Matrix matrix_2(matrix_1);
  S21Matrix matrix_E(matrix_1);

  matrix_1 *= randVal;
  matrix_2 *= 1 / randVal;
  S21Matrix matrix_1inv = matrix_1;
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_1inv.InverseMatrix()));
  EXPECT_TRUE(matrix_E.EqMatrix(matrix_1inv * matrix_1));
}

TEST(Devision, PositiveTest) {
  int row = 3;
  S21Matrix matrix_1(row, row);
  FillMatrixValue(byRand, &matrix_1);
  if (fabs(matrix_1.Determinant()) > PRECISION) {
    S21Matrix matrix_2 = 1 / matrix_1;
    S21Matrix matrix_E(matrix_1 / 0.2 / matrix_1);
    matrix_E /= 5;
    S21Matrix matrix_res = 7 / matrix_2;
    matrix_res /= matrix_1 * 7;
    EXPECT_TRUE(matrix_E == matrix_res);
  } else {
    if (!WITH_THROW) {
      EXPECT_EQ(1, 1);
    } else {
      ASSERT_THROW(1 / matrix_1, std::invalid_argument);
    }
  }
}

TEST(Devision, NegativeTest) {
  int row = 3;
  S21Matrix matrix_1(row, row);
  FillMatrixValue(byRand, &matrix_1);
  if (fabs(matrix_1.Determinant()) > PRECISION) {
    S21Matrix matrix_2 = 0 / matrix_1;
    S21Matrix matrix_E(5 * matrix_1 / matrix_1);
    matrix_E /= 5;
    ASSERT_THROW(7 / matrix_2, std::invalid_argument);
    ASSERT_THROW(matrix_E / 1e-9, std::invalid_argument);
  } else {
    if (!WITH_THROW) {
      EXPECT_EQ(1, 1);
    } else {
      ASSERT_THROW(1 / matrix_1, std::invalid_argument);
    }
  }
}

int main(int argc, char** argv) {
  srand(time_t(nullptr));
  // for (int i = 2; i < 25; i++)
  //   printf("rand%%%d=%d\n", i, std::rand()%i);
  //  printf("The division by zero or the |%.3e| is less then PRECISION=%.3e
  //  \n", 0.0, PRECISION);

  WITH_THROW = 1;
  // if (argc > 1) {
  //   int cancel_throw;
  //   sscanf(argv[1], "%d", &cancel_throw);
  //   WITH_THROW = !cancel_throw;
  // }
  // printf("WITH_THROW=%d\n", WITH_THROW);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
