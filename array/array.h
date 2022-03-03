#include <stdexcept>
#pragma once

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
 private:
  void SwapValues(T& lvalue, T& rvalue) {
    T tmp = rvalue;
    rvalue = lvalue;
    lvalue = tmp;
  }

 public:
  T data[N];
  Array() = default;
  T& operator[](size_t pos) {
    return data[pos];
  }
  const T& operator[](size_t pos) const {
    return data[pos];
  }

  const T& At(size_t idx) const {
    if (idx < N) {
      return data[idx];
    }
    throw ArrayOutOfRange();
  }
  T& At(size_t idx) {
    if (idx < N) {
      return data[idx];
    }
    throw ArrayOutOfRange();
  }

  const T& Back() const {
    return data[N - 1];
  }
  T& Back() {
    return data[N - 1];
  }

  const T& Front() const {
    return data[0];
  }
  T& Front() {
    return data[0];
  }

  const T* Data() const {
    return data;
  }
  T* Data() {
    return data;
  }

  int Size() const {
    return N;
  }
  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      data[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      SwapValues(data[i], other[i]);
    }
  }
  ~Array() = default;
};
