#pragma once
#include <stdexcept>
#include <iostream>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  explicit StringView() {
    data_ = nullptr;
    size_ = 0;
  }
  StringView(const char* arr) {  // NOLINT
    size_t size = 0;
    for (size_t i = 0; arr[i] != '\0'; ++i) {
      ++size;
    }
    data_ = arr;
    size_ = size;
  }
  explicit StringView(const char* arr, size_t size) {
    data_ = arr;
    size_ = size;
  }
  StringView(const StringView& other) {
    data_ = other.data_;
    size_ = other.size_;
  }
  ~StringView() = default;

  const char& operator[](int pos) {
    return data_[pos];
  }
  const char& operator[](int pos) const {
    return data_[pos];
  }

  const char& Front() const {
    return data_[0];
  }
  const char& Front() {
    return data_[0];
  }

  const char& Back() const {
    return data_[size_ - 1];
  }
  const char& Back() {
    return data_[size_ - 1];
  }

  const char* Data() const {
    return data_;
  }
  const char* Data() {
    return data_;
  }

  const char& At(size_t idx) const {
    if (idx < size_) {
      return data_[idx];
    }
    throw StringViewOutOfRange();
  }
  const char& At(size_t idx) {
    if (idx < size_) {
      return data_[idx];
    }
    throw StringViewOutOfRange();
  }

  bool Empty() const {
    return size_ == 0;
  }
  size_t Size() const {
    return size_;
  }
  size_t Length() const {
    return size_;
  }

  void Swap(StringView& other) {
    if (other.data_ == data_) {
      return;
    }
    auto tmp = *this;
    *this = other;
    other = tmp;
  }

  void RemovePrefix(size_t prefix_size) {
    data_ += prefix_size;
    size_ -= prefix_size;
  }
  void RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
  }
  StringView Substr(size_t pos, size_t count = -1) {
    if (pos > size_) {
      throw StringViewOutOfRange();
    }
    size_t n = Min(count, size_ - pos);
    return StringView(data_ + pos, n);
  }

 private:
  size_t size_ = 0;
  const char* data_;

  size_t Min(size_t lhs, size_t rhs) const {
    if (lhs < rhs) {
      return lhs;
    }
    return rhs;
  }

  void Swap(size_t& lhs, size_t& rhs) {
    size_t tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }
  void Swap(char& lhs, char& rhs) {
    char tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }
};
