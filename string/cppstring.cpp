#include "cppstring.h"

String::String() {
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}
String::String(size_t size, char symbol) {
  if (size == 0) {
    data_ = nullptr;
    size_ = capacity_ = 0;
  } else {
    data_ = new char[size];
    for (size_t i = 0; i < size; ++i) {
      data_[i] = symbol;
    }
    size_ = capacity_ = size;
  }
}
String::String(const char* other) {  // NOLINT
  size_t size = 0;
  for (size_t i = 0; other[i] != '\0'; ++i) {
    ++size;
  }
  data_ = new char[size];
  for (size_t i = 0; i < size; ++i) {
    data_[i] = other[i];
  }
  size_ = capacity_ = size;
}
String::String(const char* other, size_t size) {
  data_ = new char[size];
  for (size_t i = 0; i < size; ++i) {
    data_[i] = other[i];
  }
  size_ = capacity_ = size;
}
String::String(const String& other) {
  data_ = new char[other.size_ + 1];
  for (size_t i = 0; i < other.size_; ++i) {
    data_[i] = other.data_[i];
  }
  size_ = capacity_ = other.size_;
}
String::~String() {
  delete[] data_;
}

char& String::operator[](int pos) {
  return data_[pos];
}
const char& String::operator[](int pos) const {
  return data_[pos];
}

char& String::Front() const {
  return data_[0];
}
char& String::Front() {
  return data_[0];
}

char& String::Back() const {
  return data_[size_ - 1];
}
char& String::Back() {
  return data_[size_ - 1];
}

char* String::CStr() {
  return data_;
}
char* String::Data() {
  if (size_ == 0) {
    return nullptr;
  }
  return data_;
}
const char* String::CStr() const {
  return data_;
}
const char* String::Data() const {
  if (size_ == 0) {
    return nullptr;
  }
  return data_;
}

const char& String::At(size_t idx) const {
  if (idx < size_) {
    return data_[idx];
  }
  throw StringOutOfRange();
}
char& String::At(size_t idx) {
  if (idx < size_) {
    return data_[idx];
  }
  throw StringOutOfRange();
}

bool String::Empty() const {
  return size_ == 0;
}
size_t String::Size() const {
  return size_;
}
size_t String::Length() const {
  return size_;
}
size_t String::Capacity() const {
  return capacity_;
}
void String::Clear() {
  size_ = 0;
}

void String::PopBack() {
  --size_;
}
void String::PushBack(char symbol) {
  if (size_ == capacity_) {
    Resize();
  }
  data_[size_] = symbol;
  ++size_;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size == 0) {
    size_ = 0;
  } else {
    if (new_size > capacity_) {
      auto* new_data = new char[new_size];
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
    }
    if (new_size > size_) {
      for (size_t i = size_; i < new_size; ++i) {
        data_[i] = symbol;
      }
    }
    size_ = capacity_ = new_size;
  }
}
void String::Reserve(size_t new_capacity) {
  size_t n = Max(new_capacity, capacity_);
  auto* new_data = new char[n];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = n;
}
void String::ShrinkToFit() {
  auto* new_data = new char[size_];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = size_;
}

String& String::operator+=(const String& other) {
  size_t n = other.size_;
  for (size_t i = 0; i < n; ++i) {
    PushBack(other.data_[i]);
  }
  return *this;
}
String String::operator+(const String& other) const {
  size_t n = size_ + other.size_;
  String new_one;
  for (size_t i = 0; i < size_; ++i) {
    new_one.PushBack(data_[i]);
  }
  for (size_t i = 0; i < n - size_; ++i) {
    new_one.PushBack(other.data_[i]);
  }
  return new_one;
}
String String::operator+(const char* arr) const {
  size_t arr_size = 0;
  while (arr[arr_size] != '\0') {
    ++arr_size;
  }
  String new_one;
  for (size_t i = 0; i < size_; ++i) {
    new_one.PushBack(data_[i]);
  }
  for (size_t i = 0; i < arr_size; ++i) {
    new_one.PushBack(arr[i]);
  }
  return new_one;
}
String& String::operator=(const String& other) {
  if (other.size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    size_ = capacity_ = 0;
  } else if (other.capacity_ == capacity_) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
    size_ = other.size_;
  } else {
    auto* new_data = new char[other.capacity_];
    for (size_t i = 0; i < other.size_; ++i) {
      new_data[i] = other.data_[i];
    }
    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;
  }
  return *this;
}
String operator+(char const* arr, String str) {
  size_t arr_size = 0;
  while (arr[arr_size] != '\0') {
    ++arr_size;
  }
  String new_one;
  for (size_t i = 0; i < str.Size(); ++i) {
    new_one.PushBack(str.Data()[i]);
  }
  for (size_t i = 0; i < arr_size; ++i) {
    new_one.PushBack(arr[i]);
  }
  return new_one;
}

bool operator==(const String& str, const String& other) {
  if (other.Size() != str.Size()) {
    return false;
  }
  if (str.Data() == nullptr) {
    return true;
  }
  for (size_t i = 0; i < str.Size(); ++i) {
    if (str.Data()[i] != other.Data()[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(const String& str, const String& other) {
  return !(str == other);
}
bool operator<(const String& str, const String& other) {
  if (str.Empty() && other.Empty()) {
    return false;
  }
  if (str.Empty()) {
    return true;
  }
  if (other.Empty()) {
    return false;
  }
  size_t n = Min(other.Size(), str.Size());
  size_t i = 0;
  bool flag_not_equal_found = false;
  for (; i < n; ++i) {
    if (str.Data()[i] != other.Data()[i]) {
      flag_not_equal_found = true;
      break;
    }
  }
  if (!flag_not_equal_found && other.Size() <= str.Size()) {
    return false;
  }
  if (!flag_not_equal_found && other.Size() > str.Size()) {
    return true;
  }
  return str.Data()[i] < other.Data()[i];
}
bool operator>(const String& str, const String& other) {
  return (other < str);
}
bool operator<=(const String& str, const String& other) {
  return (str < other) || (str == other);
}
bool operator>=(const String& str, const String& other) {
  return (other < str) || (str == other);
}

std::ostream& operator<<(std::ostream& os, const String& num) {
  for (size_t i = 0; i < num.Size(); ++i) {
    os << num.Data()[i];
  }
  return os;
}

size_t String::Max(size_t lhs, size_t rhs) const {
  if (lhs > rhs) {
    return lhs;
  }
  return rhs;
}

size_t Min(size_t lhs, size_t rhs) {
  if (lhs < rhs) {
    return lhs;
  }
  return rhs;
}
size_t Max(size_t lhs, size_t rhs) {
  if (lhs > rhs) {
    return lhs;
  }
  return rhs;
}

void String::Swap(String& other) {
  auto* new_data_other = new char[capacity_];
  auto* new_data = new char[other.capacity_];
  if (other.size_ < size_) {
    for (size_t i = 0; i < other.size_; ++i) {
      new_data[i] = other.data_[i];
      new_data_other[i] = data_[i];
    }
    for (size_t i = other.size_; i < size_; ++i) {
      new_data_other[i] = data_[i];
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = other.data_[i];
      new_data_other[i] = data_[i];
    }
    for (size_t i = size_; i < other.size_; ++i) {
      new_data[i] = other.data_[i];
    }
  }
  Swap(other.size_, size_);
  Swap(other.capacity_, capacity_);
  delete[] data_;
  delete[] other.data_;
  data_ = new_data;
  other.data_ = new_data_other;
}
void String::Swap(size_t& lhs, size_t& rhs) {
  size_t tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}
void String::Swap(char& lhs, char& rhs) {
  char tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

void String::Resize() {
  if (capacity_ == 0) {
    capacity_ = 1;
  }
  capacity_ *= 2;
  auto* new_data = new char[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
}
