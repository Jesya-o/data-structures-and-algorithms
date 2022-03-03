#pragma once
template <typename T, typename U, typename V>
void Merge(T* first_begin, T* first_end, U* second_begin, U* second_end, V* out) {
  int i_first = 0, i_second = 0, i_out = 0;
  int end_first = first_end - first_begin;
  int end_second = second_end - second_begin;
  while (i_first < end_first && i_second < end_second) {
    if (first_begin[i_first] < second_begin[i_second]) {
      out[i_out] = static_cast<V>(first_begin[i_first]);
      ++i_out;
      ++i_first;
    } else {
      out[i_out] = static_cast<V>(second_begin[i_second]);
      ++i_out;
      ++i_second;
    }
  }
  while (i_first < end_first) {
    out[i_out] = static_cast<V>(first_begin[i_first]);
    ++i_out;
    ++i_first;
  }
  while (i_second < end_second) {
    out[i_out] = static_cast<V>(second_begin[i_second]);
    ++i_out;
    ++i_second;
  }
}