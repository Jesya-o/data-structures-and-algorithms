#pragma once
#include <stdexcept>
#include <iostream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t Rows, size_t Cols>
class Matrix {
 public:
  T curr[Rows][Cols];

  size_t RowsNumber() const {
    return Rows;
  }
  size_t ColumnsNumber() const {
    return Cols;
  }

  T &operator()(size_t row, size_t col) {
    return curr[row][col];
  }
  const T &operator()(size_t row, size_t col) const {
    return curr[row][col];
  }

  T &At(size_t row, size_t col) {
    if (col < Cols && row < Rows) {
      return curr[row][col];
    }
    throw MatrixOutOfRange();
  }
  const T &At(size_t row, size_t col) const {
    if (col < Cols && row < Rows) {
      return curr[row][col];
    }
    throw MatrixOutOfRange();
  }

  Matrix<T, Rows, Cols> &operator+=(const Matrix<T, Rows, Cols> &other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        curr[i][j] += other.curr[i][j];
      }
    }
    return *this;
  }
  Matrix<T, Rows, Cols> &operator-=(const Matrix<T, Rows, Cols> &other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        curr[i][j] -= other.curr[i][j];
      }
    }
    return *this;
  }

  Matrix<T, Rows, Cols> &operator*=(const int64_t &num) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; j++) {
        curr[i][j] *= num;
      }
    }
    return *this;
  }
  Matrix<T, Rows, Cols> &operator/=(const int64_t &num) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; j++) {
        curr[i][j] /= num;
      }
    }
    return *this;
  }

  Matrix<T, Rows, Cols> &operator*=(const Matrix<T, Cols, Cols> &other) {
    T line[Cols];
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        line[j] = 0;
        for (size_t k = 0; k < Cols; ++k) {
          line[j] += curr[i][k] * other.curr[k][j];
        }
      }
      for (size_t j = 0; j < Cols; ++j) {
        curr[i][j] = line[j];
      }
    }
    return *this;
  }
};

template <class T, size_t Rows, size_t Cols>
bool operator==(const Matrix<T, Cols, Rows> &matrix, const Matrix<T, Cols, Rows> &other) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Cols; j++) {
      if (matrix.curr[i][j] != other.curr[i][j]) {
        return false;
      }
    }
  }
  return true;
}
template <class T, size_t Rows, size_t Cols>
bool operator!=(const Matrix<T, Cols, Rows> &matrix, const Matrix<T, Cols, Rows> &other) {
  return !(matrix == other);
}

template <class T, size_t Rows, size_t Cols>
Matrix<T, Cols, Rows> GetTransposed(Matrix<T, Rows, Cols> &matrix) {
  Matrix<T, Cols, Rows> new_matrix;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Cols; j++) {
      new_matrix.curr[j][i] = matrix.curr[i][j];
    }
  }
  return new_matrix;
}

template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator*(const int64_t num, const Matrix<T, Rows, Cols> matrix) {
  Matrix<T, Rows, Cols> new_matrix = matrix;
  new_matrix *= num;
  return new_matrix;
}
template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Cols> matrix, const int64_t num) {
  Matrix<T, Rows, Cols> new_matrix = matrix;
  new_matrix *= num;
  return new_matrix;
}
template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator/(const Matrix<T, Rows, Cols> matrix, const int64_t num) {
  Matrix<T, Rows, Cols> new_matrix = matrix;
  new_matrix /= num;
  return new_matrix;
}

template <class T, size_t N, size_t M, size_t P>
Matrix<T, N, P> operator*(const Matrix<T, N, M> &a, const Matrix<T, M, P> &b) {
  Matrix<T, N, P> new_matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < P; ++j) {
      new_matrix.curr[i][j] = 0;
      for (size_t k = 0; k < M; ++k) {
        new_matrix.curr[i][j] += a.curr[i][k] * b.curr[k][j];
      }
    }
  }
  return new_matrix;
}

template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols> &matrix, const Matrix<T, Rows, Cols> &other) {
  Matrix<T, Rows, Cols> new_matrix = matrix;
  new_matrix += other;
  return new_matrix;
}
template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols> &matrix, const Matrix<T, Rows, Cols> &other) {
  Matrix<T, Rows, Cols> new_matrix = matrix;
  new_matrix -= other;
  return new_matrix;
}

template <class T, size_t Rows, size_t Cols>
std::istream &operator>>(std::istream &is, Matrix<T, Rows, Cols> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      is >> matrix.curr[i][j];
    }
  }
  return is;
}
template <class T, size_t Rows, size_t Cols>
std::ostream &operator<<(std::ostream &os, const Matrix<T, Rows, Cols> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols - 1; ++j) {
      os << matrix.curr[i][j] << ' ';
    }
    os << matrix.curr[i][Cols - 1] << '\n';
  }
  return os;
}