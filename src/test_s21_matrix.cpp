#include <cmath>

#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

// Тест конструктора по умолчанию (создает 3*3 матрицу, заполненную нулями)
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getRows(), 3);
  EXPECT_EQ(m.getCols(), 3);
  for (int i = 0; i < m.getRows(); ++i) {
    for (int j = 0; j < m.getCols(); ++j) {
      EXPECT_DOUBLE_EQ(m(i, j), 0.0);
    }
  }
}

// Тест параметризованного конструктора (например, 4*5)
TEST(S21MatrixTest, ParameterConstructor) {
  S21Matrix m(4, 5);
  EXPECT_EQ(m.getRows(), 4);
  EXPECT_EQ(m.getCols(), 5);
  for (int i = 0; i < m.getRows(); ++i) {
    for (int j = 0; j < m.getCols(); ++j) {
      EXPECT_DOUBLE_EQ(m(i, j), 0.0);
    }
  }
}

// Тест конструктора копирования и оператора сравнения
TEST(S21MatrixTest, CopyConstructorAndEquality) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  S21Matrix m2(m1);
  EXPECT_TRUE(m1 == m2);
}

// Тест операции сложения матриц
TEST(S21MatrixTest, SumMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;

  S21Matrix m3 = m1 + m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(m3(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(m3(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(m3(1, 1), 12.0);
}

// Тест операции вычитания матриц
TEST(S21MatrixTest, SubMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 5.0;
  m1(0, 1) = 7.0;
  m1(1, 0) = 9.0;
  m1(1, 1) = 11.0;

  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  S21Matrix m3 = m1 - m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(m3(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m3(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m3(1, 1), 7.0);
}

// Тест операции умножения матриц
TEST(S21MatrixTest, MulMatrix) {
  S21Matrix m1(2, 3), m2(3, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  m2(0, 0) = 7.0;
  m2(0, 1) = 8.0;
  m2(1, 0) = 9.0;
  m2(1, 1) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;
  S21Matrix m3 = m1 * m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(m3(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(m3(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(m3(1, 1), 154.0);
}

// Тест умножения матрицы на число
TEST(S21MatrixTest, MulNumber) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;
  S21Matrix m2 = m * 2.0;
  EXPECT_DOUBLE_EQ(m2(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m2(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m2(1, 1), 8.0);
}

// Тест транспонирования матрицы
TEST(S21MatrixTest, Transpose) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;
  S21Matrix t = m.Transpose();
  EXPECT_EQ(t.getRows(), 3);
  EXPECT_EQ(t.getCols(), 2);
  EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(t(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(t(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(t(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(t(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(t(2, 1), 6.0);
}

// Тест вычисления определителя
TEST(S21MatrixTest, Determinant) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(m.Determinant(), -2.0);
}

// Тест вычисления обратной матрицы
TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix m(2, 2);
  m(0, 0) = 4.0;
  m(0, 1) = 7.0;
  m(1, 0) = 2.0;
  m(1, 1) = 6.0;
  S21Matrix inv = m.InverseMatrix();
  EXPECT_NEAR(inv(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(inv(0, 1), -0.7, 1e-7);
  EXPECT_NEAR(inv(1, 0), -0.2, 1e-7);
  EXPECT_NEAR(inv(1, 1), 0.4, 1e-7);
}

// Тест на некорректные размеры (проверка выброса исключения allocateMatrix)
TEST(S21MatrixTest, InvalidMatrixSize) {
  EXPECT_THROW(S21Matrix(-1, 5), std::invalid_argument);
  EXPECT_THROW(S21Matrix(5, -1), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
}

TEST(S21MatrixTest, DestructorDoesNotCrash) {
  {
    S21Matrix m(10, 10);
    m(5, 5) = 42.0;
  }
  SUCCEED();
}

TEST(S21MatrixDeathTest, DoubleFreeDoesNotCrash) {
  S21Matrix *p = new S21Matrix(3, 3);
  delete p;

  SUCCEED();
}

// Тест конструктора перемещения
TEST(S21MatrixTest, MoveConstructor) {
  // Создаём и заполняем исходную матрицу 2×2
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  // Вызываем конструктор перемещения
  S21Matrix m2(std::move(m1));

  // 1) Проверяем, что m2 получил все данные
  EXPECT_EQ(m2.getRows(), 2);
  EXPECT_EQ(m2.getCols(), 2);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m2(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m2(1, 1), 4.0);

  // размеры сброшены в 0, и доступ к элементам бросает исключение
  EXPECT_EQ(m1.getRows(), 0);
  EXPECT_EQ(m1.getCols(), 0);
  EXPECT_THROW(m1(0, 0), std::out_of_range);
}

// Увеличение размеров:
TEST(S21MatrixTest, ResizeIncrease) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(1, 1) = 2.0;
  m.resize(3, 3);
  EXPECT_EQ(m.getRows(), 3);
  EXPECT_EQ(m.getCols(), 3);
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(2, 2), 0.0);
}

// Уменьшение размеров:
TEST(S21MatrixTest, ResizeDecrease) {
  S21Matrix m(3, 3);
  m(2, 2) = 9.0;
  m.resize(2, 2);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 2);
}

// Проверка на ошибки при некорректных параметрах:
TEST(S21MatrixTest, ResizeInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.resize(0, 2), std::invalid_argument);
  EXPECT_THROW(m.resize(2, -1), std::invalid_argument);
}

//  Проверка равных матриц:
TEST(S21MatrixTest, EqMatrixEqual) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = m2(0, 0) = 1.00000001;
  m1(0, 1) = m2(0, 1) = 2.0;
  m1(1, 0) = m2(1, 0) = 3.0;
  m1(1, 1) = m2(1, 1) = 4.0;
  EXPECT_TRUE(m1.EqMatrix(m2));
}

// Проверка почти равных матриц:
TEST(S21MatrixTest, EqMatrixNearlyEqual) {
  S21Matrix m1(1, 1);
  S21Matrix m2(1, 1);
  m1(0, 0) = 1.0000001;
  m2(0, 0) = 1.0000002;
  EXPECT_TRUE(m1.EqMatrix(m2));
}

// Проверка на неравные (разные значения)
TEST(S21MatrixTest, EqMatrixDifferentValues) {
  S21Matrix m1(1, 1);
  S21Matrix m2(1, 1);
  m1(0, 0) = 1.0;
  m2(0, 0) = 1.1;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

// Проверка на неравные (разные размеры):
TEST(S21MatrixTest, EqMatrixDifferentSizes) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, CalcComplements1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 42.0;
  S21Matrix expected(1, 1);
  expected(0, 0) = 42.0;
  S21Matrix result = m.CalcComplements();
  EXPECT_TRUE(result == expected);
}

TEST(S21MatrixTest, CalcComplements2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  S21Matrix result = m.CalcComplements();

  // Алгебраические дополнения:
  // |  4 -3 |
  // | -2  1 |
  S21Matrix expected(2, 2);
  expected(0, 0) = 4;
  expected(0, 1) = -3;
  expected(1, 0) = -2;
  expected(1, 1) = 1;

  EXPECT_TRUE(result == expected);
}
