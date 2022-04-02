#include <iostream>
#include <iomanip>
#include <stdexcept>

// structure of Point with needed operators
struct Point {
  int64_t x = 0;  // can be modified to double
  int64_t y = 0;  // then area function returning type
  // should be made long double (the maximum area size would be less)
  bool operator<(Point b) const {
    return x < b.x || (x == b.x && y < b.y);
  }
  bool operator>(Point b) const {
    return x > b.x || (x == b.x && y > b.y);
  }
};

// exception if corrupting array size
class OutOfRange : public std::out_of_range {
 public:
  OutOfRange() : std::out_of_range("OutOfRange") {
  }
};

template <typename T>
class Array {
 public:
  Array() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
  explicit Array(size_t size, T elem) {  // constructing array filled by element
    if (size == 0) {
      data_ = nullptr;
      size_ = capacity_ = 0;
    } else {
      data_ = new T[size];
      for (size_t i = 0; i < size; ++i) {
        data_[i] = elem;
      }
      size_ = capacity_ = size;
    }
  }
  explicit Array(const T* arr, size_t n) {
    data_ = new T[n];
    for (size_t i = 0; i < n; ++i) {
      data_[i] = arr[i];
    }
    size_ = capacity_ = n;
  }

  Array(const Array& other) {
    data_ = new T[other.size_];
    for (size_t i = 0; i < other.size_; ++i) {
      data_[i] = other.data_[i];
    }
    size_ = capacity_ = other.size_;
  }
  Array& operator=(const Array& other) {
    if (other.Data() == data_) {
      return *this;
    }
    if (other.Size() == 0) {
      delete[] data_;
      data_ = nullptr;
      size_ = capacity_ = 0;
    } else if (other.capacity_ <= capacity_) {
      for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
      size_ = other.size_;
    } else {
      auto* new_data = new T[other.capacity_];
      for (size_t i = 0; i < other.Size(); ++i) {
        new_data[i] = other.Data()[i];
      }
      delete[] data_;
      data_ = new_data;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  Array(Array&& other) noexcept {
    data_ = new T[other.size_];
    for (size_t i = 0; i < other.size_; ++i) {
      data_[i] = other.data_[i];
    }
    other.data_ = nullptr;
    size_ = capacity_ = other.size_;
  }
  Array& operator=(Array&& other) noexcept {
    if (other.Data() == data_) {
      return *this;
    }
    if (other.Size() == 0) {
      delete[] data_;
      data_ = nullptr;
      other.data_ = nullptr;
      size_ = capacity_ = 0;
    } else if (other.capacity_ <= capacity_) {
      for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
      size_ = other.size_;
    } else {
      auto* new_data = new T[other.capacity_];
      for (size_t i = 0; i < other.Size(); ++i) {
        new_data[i] = other.Data()[i];
      }
      delete[] data_;
      data_ = new_data;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  ~Array() {
    delete[] data_;
  }

  T& operator[](size_t pos) {
    return data_[pos];
  }
  const T& operator[](size_t pos) const {
    return data_[pos];
  }

  size_t Begin() {
    return 0;
  }
  size_t End() {
    return size_ - 1;
  }

  [[nodiscard]] const T& Front() const {
    return data_[0];
  }
  T& Front() {
    return data_[0];
  }

  [[nodiscard]] const T& Back() const {
    return data_[size_ - 1];
  }
  T& Back() {
    return data_[size_ - 1];
  }

  [[nodiscard]] const T* Data() const {
    if (size_ == 0) {
      return nullptr;
    }
    return data_;
  }
  T* Data() {
    if (size_ == 0) {
      return nullptr;
    }
    return data_;
  }

  [[nodiscard]] const T& At(size_t idx) const {
    if (idx < size_) {
      return data_[idx];
    }
    throw OutOfRange();
  }
  T& At(size_t idx) {
    if (idx < size_) {
      return data_[idx];
    }
    throw OutOfRange();
  }

  [[nodiscard]] bool Empty() const {
    return size_ == 0;
  }
  [[nodiscard]] size_t Size() const {
    return size_;
  }
  [[nodiscard]] size_t Capacity() const {
    return capacity_;
  }
  void Clear() {
    size_ = 0;
  }

  void PopBack() {
    --size_;
  }
  void PushBack(T elem) {
    if (size_ == capacity_) {
      Resize();
    }
    data_[size_] = elem;
    ++size_;
  }

  void Resize(size_t new_size, T elem) {
    if (new_size == 0) {
      size_ = 0;
    } else {
      if (new_size > capacity_) {
        auto* new_data = new T[new_size];
        for (size_t i = 0; i < size_; ++i) {
          new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
      }
      if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
          data_[i] = elem;
        }
      }
      size_ = capacity_ = new_size;
    }
  }
  void Reserve(size_t new_capacity) {
    size_t n = std::max(new_capacity, capacity_);
    auto* new_data = new T[n];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = n;
  }
  void ShrinkToFit() {
    auto* new_data = new T[size_];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
  std::ostream& operator<<(std::ostream& os) {
    for (size_t i = 0; i < size_; ++i) {
      os << data_[i];
    }
    return os;
  }

  T* data_;
private:
  size_t size_ = 0;
  size_t capacity_ = 1;
  void Resize() {
    if (capacity_ == 0) {
      capacity_ = 1;
    }
    capacity_ *= 2;
    auto* new_data = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }
};

template <typename T>
size_t Partition(Array<T>& list, size_t l, size_t r) {
  size_t pivot_idx = (l + r) / 2;
  T pivot_value = list[pivot_idx];
  size_t i = l, j = r;
  while (i <= j) {
    while (list[i] < pivot_value) {
      ++i;
    }
    while (list[j] > pivot_value) {
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(list[i], list[j]);
    ++i;
    --j;
  }
  return j;
}

template <typename T>
void QuickSort(Array<T>& list, size_t l, size_t r) {
  if (l < r) {
    size_t pivot_idx = Partition(list, l, r);
    QuickSort(list, l, pivot_idx);
    QuickSort(list, pivot_idx + 1, r);
  }
}

bool Right(Point a, Point b, Point c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool Left(Point a, Point b, Point c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

void Graham(Array<Point>& a) {
  if (a.Size() == 1) {
    return;
  }
  QuickSort(a, a.Begin(), a.End());
  Point p1 = a[0], p2 = a.Back();
  Array<Point> up, down;
  up.PushBack(p1);
  down.PushBack(p1);
  for (size_t i = 1; i < a.Size(); ++i) {
    if (i == a.Size() - 1 || Right(p1, a[i], p2)) {
      while (up.Size() >= 2 && !Right(up[up.Size() - 2], up[up.Size() - 1], a[i])) {
        up.PopBack();
      }
      up.PushBack(a[i]);
    }
    if (i == a.Size() - 1 || Left(p1, a[i], p2)) {
      while (down.Size() >= 2 && !Left(down[down.Size() - 2], down[down.Size() - 1], a[i])) {
        down.PopBack();
      }
      down.PushBack(a[i]);
    }
  }
  a.Clear();
  for (size_t i = 0; i < up.Size(); ++i) {
    a.PushBack(up[i]);
  }
  for (size_t i = down.Size() - 2; i > 0; --i) {
    a.PushBack(down[i]);
  }
}

size_t HalfArea(Array<Point> arr) {
  size_t n = arr.Size();
  int64_t sum = 0;
  Point next;
  Point first = arr.Back();
  arr.PopBack();
  Point curr = first;
  for (size_t i = 0; i < n - 1; ++i) {
    next = arr.Back();
    arr.PopBack();
    sum += curr.x * next.y - curr.y * next.x;
    curr = next;
  }
  sum += curr.x * first.y - curr.y * first.x;
  return std::abs(sum);
}

int main() {
  size_t n;
  std::cin >> n;
  Array<Point> arr;
  Point curr;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> curr.x >> curr.y;
    arr.PushBack(curr);
  }
  Graham(arr);
  size_t k = arr.Size();
  std::cout << k << '\n';
  for (size_t i = 0; i < k; ++i) {
    std::cout << arr[i].x << " " << arr[i].y << '\n';
  }
  size_t s = HalfArea(arr);
  if (s % 2 == 0) {
    std::cout << s / 2 << ".0";
  } else {
    std::cout << s / 2 << ".5";
  }
}
