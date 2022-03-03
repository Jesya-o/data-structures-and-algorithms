#pragma once
template <typename T>
bool BinarySearch(const T* begin, const T* end, const T& target) {
  int left = 0;
  int right = end - begin - 1;
  int mid;
  while (left <= right) {
    mid = (left + right) / 2;
    if (begin[mid] < target) {
      left = mid + 1;
    } else if (target < begin[mid]) {
      right = mid - 1;
    } else {
      return true;
    }
  }
  return false;
}