#pragma once
template <typename U>
void Swap(U& lhs, U& rhs) {
  U tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}
template <typename T>
int Partition(T* begin, T* real_end) {
  int pivot_idx = (real_end - begin) / 2;
  T pivot_value = begin[pivot_idx];
  int i = 0, j = real_end - begin;
  while (i <= j) {
    while (begin[i] < pivot_value) {
      ++i;
    }
    while (pivot_value < begin[j]) {
      --j;
    }
    if (i >= j) {
      break;
    }
    Swap(begin[i++], begin[j--]);
  }
  return j;
}
template <typename T>
void Sort(T* begin, T* end) {
  if (begin + 1 < end) {
    int pivot_idx = Partition(begin, end - 1);
    Sort(begin, begin + pivot_idx + 1);
    Sort(begin + pivot_idx + 1, end);
  }
}