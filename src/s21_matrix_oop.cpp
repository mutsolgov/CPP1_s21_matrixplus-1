#include "s21_matrix_oop.h"

#include <iomanip>
#include <stdexcept>

// вспомогательный метод для выделения памяти
void S21Matrix::allocateMatrix() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Размеры матрицы должны быть положительными.");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    // Инициализируем нулями
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

// Вспомогательный метод для освобождения памяти
void S21Matrix::freeMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// Вспомогательный метод копирования матрицы
void S21Matrix::copyMatrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  allocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Конструктор по умолчанию (создаем, например, 3*3 матрицу)
S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

// Параметризованный конструктор
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Размеры матрицы должны быть положительными.");
  }
  allocateMatrix();
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(0), cols_(0), matrix_(nullptr) {
  copyMatrix(other);
}

// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// Деструктор
S21Matrix::~S21Matrix() { freeMatrix(); }

// Геттеры
int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

// Метод изменения размеров матрицы
void S21Matrix::resize(int new_rows, int new_cols) {
  if (new_rows <= 0 || new_cols <= 0) {
    throw std::invalid_argument(
        "Новые размеры матрицы должны быть положительными.");
  }
  // Создаем новую матрицу
  double **new_matrix = new double *[new_rows];
  for (int i = 0; i < new_rows; i++) {
    new_matrix[i] = new double[new_cols];
    for (int j = 0; j < new_cols; j++) {
      new_matrix[i][j] = 0.0;
    }
  }
  // Копируем старые значения (до минимума старых и новых размеров)
  int min_rows = (new_rows < rows_) ? new_rows : rows_;
  int min_cols = (new_cols < cols_) ? new_cols : cols_;
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < min_cols; j++) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }
  // Освобождаем старую память и переназначаем
  freeMatrix();
  matrix_ = new_matrix;
  rows_ = new_rows;
  cols_ = new_cols;
}

// Проверка равенства матриц (с учетом небольшого допуска)
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    return false;
  const double tol = 1e-7;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > tol) {
        return false;
      }
    }
  }
  return true;
}

// Сложение матриц (изменяет текущую матрицу)
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Матрицы имеют разные размеры для сложения.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Вычитание матриц (изменяет текущую матрицу)
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Матрицы имеют разные размеры для вычитания.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Умножение матрицы на число (изменяет текущую матрицу)
void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// Умножение матрицы на другую матрицу (изменяет текущую матрицу)
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Некорректные размеры матриц для умножения.");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0.0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      result.matrix_[i][j] = sum;
    }
  }
  // Заменяем текущую матрицу результатом
  freeMatrix();
  rows_ = result.rows_;
  cols_ = result.cols_;
  allocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = result.matrix_[i][j];
    }
  }
}

// Возвращает транспонированную матрицу (не изменяет текущую)
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

// Рекурсивное вычисление определителя
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Определитель можно вычислять только для квадратных матриц.");
  }
  // Базовый случай: 1*1
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  // Базовый случай: 2*2
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double det = 0.0;
  for (int col = 0; col < cols_; col++) {
    // Создаем минор
    S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
    for (int i = 1; i < rows_; i++) {
      int minor_j = 0;
      for (int j = 0; j < cols_; j++) {
        if (j == col)
          continue;
        minorMatrix.matrix_[i - 1][minor_j] = matrix_[i][j];
        minor_j++;
      }
    }
    double sign = ((col % 2) == 0) ? 1.0 : -1.0;
    det += sign * matrix_[0][col] * minorMatrix.Determinant();
  }
  return det;
}

// Вычисление матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Матрица должна быть квадратной для вычисления алгебраических "
        "дополнений.");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
    return result;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // Создаем минор для элемента (i,j)
      S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
      int minor_i = 0;
      for (int mi = 0; mi < rows_; mi++) {
        if (mi == i)
          continue;
        int minor_j = 0;
        for (int mj = 0; mj < cols_; mj++) {
          if (mj == j)
            continue;
          minorMatrix.matrix_[minor_i][minor_j] = matrix_[mi][mj];
          minor_j++;
        }
        minor_i++;
      }
      double sign = (((i + j) % 2) == 0) ? 1.0 : -1.0;
      result.matrix_[i][j] = sign * minorMatrix.Determinant();
    }
  }
  return result;
}

// Вычисление обратной матрицы
S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (std::fabs(det) < 1e-7) {
    throw std::domain_error(
        "Определитель равен нулю, обратная матрица не существует.");
  }
  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  transposed.MulNumber(1.0 / det);
  return transposed;
}

// Перегрузка оператора индексации с проверкой границ
double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Индексы выходят за пределы матрицы.");
  }
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Индексы выходят за пределы матрицы.");
  }
  return matrix_[i][j];
}

// Перегрузка оператора +
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Размеры матриц не совпадают для сложения.");
  }
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// Перегрузка оператора -
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Размеры матриц не совпадают для вычитания.");
  }
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// Перегрузка оператора * для матричного умножения
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Некорректные размеры для умножения матриц.");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0.0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      result.matrix_[i][j] = sum;
    }
  }
  return result;
}

// Перегрузка оператора * для умножения на число
S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

// Перегрузка оператора присваивания (копирование)
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other)
    return *this;
  freeMatrix();
  copyMatrix(other);
  return *this;
}

// Перегрузка оператора присваивания (перемещение)
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this == &other)
    return *this;
  freeMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}

// Перегрузка оператора +=
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

// Перегрузка оператора -=
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

// Перегрузка оператора *= для матричного умножения
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  *this = (*this) * other;
  return *this;
}

// Перегрузка оператора *= для умножения на число
S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

// Перегрузка оператора ==
bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}