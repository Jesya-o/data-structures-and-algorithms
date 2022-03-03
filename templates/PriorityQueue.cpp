#pragma once
int Parent(int i) {
  return (i - 1) / 2;
}

int LeftSon(int i) {
  return 2 * i + 1;
}

int RightSon(int i) {
  return 2 * i + 2;
}

template <typename U>
void Swap(U& a, U& b) {
  U tmp = a;
  a = b;
  b = tmp;
}

template <typename U>
void PushHeap(U* l, U* r) {
  int i = r - l - 1;
  int parental_i = Parent(i);
  if (i > 0 && l[parental_i] < l[i]) {
    Swap(l[parental_i], l[i]);
    PushHeap(l, l + parental_i + 1);
  }
}

template <typename U>
void SiftDown(U* l, U* r, int idx) {
  if (l < r) {
    int left_i = LeftSon(idx);
    int right_i = RightSon(idx);
    int largest_i = idx;
    if (l + left_i < r && (l[largest_i] < l[left_i])) {
      largest_i = left_i;
    }
    if (l + right_i < r && (l[largest_i] < l[right_i])) {
      largest_i = right_i;
    }
    if (largest_i != idx) {
      Swap(l[idx], l[largest_i]);
      SiftDown(l, r, largest_i);
    }
  }
}
template <typename U>
void PopHeap(U* l, U* r) {
  Swap(l[0], l[r - l - 1]);
  SiftDown(l, r - 1, 0);
}