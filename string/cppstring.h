#pragma once
#include <stdexcept>
#include <iostream>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  explicit String();
  explicit String(size_t size, char symbol);

  String(const char* other);  // NOLINT

  explicit String(const char* other, size_t size);

  String(const String& other);

  char& operator[](int pos);
  const char& operator[](int pos) const;

  char& Front() const;
  char& Front();

  char& Back() const;
  char& Back();

  char* CStr();
  char* Data();
  const char* CStr() const;
  const char* Data() const;

  const char& At(size_t idx) const;
  char& At(size_t idx);

  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();

  void Swap(String& other);

  void PopBack();
  void PushBack(char symbol);

  String& operator+=(const String& other);

  void Resize(size_t new_size, char symbol);

  void Reserve(size_t new_capacity);

  void ShrinkToFit();

  String operator+(const String& other) const;
  String operator+(char const* arr) const;

  String& operator=(const String&);

  friend std::ostream& operator<<(std::ostream& os, const String& num);

  friend bool operator==(const String& str, const String& other);
  friend bool operator!=(const String& str, const String& other);
  friend bool operator<(const String& str, const String& other);
  friend bool operator>(const String& str, const String& other);
  friend bool operator<=(const String& str, const String& other);
  friend bool operator>=(const String& str, const String& other);
  ~String();

 private:
  size_t size_ = 0;
  size_t capacity_ = 1;
  char* data_;

  size_t Max(size_t lhs, size_t rhs) const;

  void Swap(char& lhs, char& rhs);
  void Swap(size_t& lhs, size_t& rhs);
  void Resize();
};

String operator+(char const* arr, String str);
size_t Min(size_t lhs, size_t rhs);
size_t Max(size_t lhs, size_t rhs);
