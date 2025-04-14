#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

class S21Matrix {
public:
  S21Matrix();                       // Конструктор по умолчанию (напримерб 3*3)
  S21Matrix(int rows, int cols);     // Параметризованный конструктор
  S21Matrix(const S21Matrix &other); // Конструктор копирования
  S21Matrix(S21Matrix &&other) noexcept; // Конструктор перемещения

  // Деструктор
  ~S21Matrix();

  // Геттеры и сеттеры
  int getRows() const;
  int getCols() const;
  // Изменение размеров матрицы: при увеличении добавляется нули, при уменьшении
  // - отбрасываются элементы.
  void resize(int new_rows, int new_cols);

  // Методы операций над матрицами
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other); // Прибавляет другую матрицу
  void SubMatrix(const S21Matrix &other); // Вычитает другую матрицу
  void MulNumber(double num);             // Умножение на число
  void MulMatrix(const S21Matrix &other); // Умножение матриц
  S21Matrix Transpose() const;            // Транспортирование
  S21Matrix CalcComplements() const;      // Матрица алгебраических дополнений
  double Determinant() const;             // Определитель
  S21Matrix InverseMatrix() const;        // Обратная матрица

  // Перегрузка операторов
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);

  bool operator==(const S21Matrix &other) const;

  // Индексация: доступ к элементу по индексу (i, j) с проверкой границ.
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;

private:
  int rows_{0};
  int cols_{0};
  double **matrix_{nullptr};

  // Вспомогательные методы для выделения и освобождения памяти
  void allocateMatrix();
  void freeMatrix();
  void copyMatrix(const S21Matrix &other);
};

#endif