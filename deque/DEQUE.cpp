#include <iostream>

struct Deque {
  int elem = 0;
  Deque* next = nullptr;
  Deque* prev = nullptr;
};

struct Node {
  Deque* pbeg = nullptr;
  Deque* pend = nullptr;
  int size = 0;
};

void PushBack(Node* d, int elem) {
  auto* pd = new Deque{elem, nullptr, nullptr};
  pd->elem = elem;
  pd->next = nullptr;
  if (d->size != 0) {
    d->pend->next = pd;
    pd->prev = d->pend;
    d->pend = pd;
  } else {
    pd->prev = nullptr;
    d->pbeg = d->pend = pd;
  }
  d->size++;
}

void PushFront(Node* d, int elem) {
  auto* pd = new Deque{elem, nullptr, nullptr};
  if (d->size == 0) {
    pd->next = nullptr;
    d->pbeg = d->pend = pd;
  } else {
    d->pbeg->prev = pd;
    pd->next = d->pbeg;
    d->pbeg = pd;
  }
  d->size++;
}

void PopFront(Node* d) {
  if (d->pbeg != nullptr) {
    d->pbeg = d->pbeg->next;
    d->size--;
  }
}

void PopBack(Node* d) {
  if (d->pend != nullptr) {
    d->pend = d->pend->prev;
    d->size--;
  }
}

int Front(Node* d) {
  return d->pbeg->elem;
}

int Back(Node* d) {
  return d->pend->elem;
}

int Size(Node* d) {
  return d->size;
}

void Clear(Node* d) {
  while (d->size != 0) {
    PopFront(d);
  }
}

void Action(int k) {
  int n;
  char* command = new char[10];
  Node* d = new Node;
  for (int i = 0; i < k; i++) {
    std::cin >> command;
    if (command[0] == 'p' && command[1] == 'u' && command[5] == 'f') {
      std::cin >> n;
      PushFront(d, n);
      std::cout << "ok" << std::endl;
    } else if (command[0] == 'p' && command[1] == 'u' && command[5] == 'b') {
      std::cin >> n;
      PushBack(d, n);
      std::cout << "ok" << std::endl;
    } else if (command[0] == 'p' && command[4] == 'f') {
      if (d->size == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << Front(d) << std::endl;
        PopFront(d);
      }
    } else if (command[0] == 'p' && command[4] == 'b') {
      if (d->size == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << Back(d) << std::endl;
        PopBack(d);
      }
    } else if (command[0] == 'f') {
      if (d->size == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << Front(d) << std::endl;
      }
    } else if (command[0] == 'b') {
      if (d->size == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << Back(d) << std::endl;
      }
    } else if (command[0] == 's') {
      std::cout << Size(d) << std::endl;
    } else if (command[0] == 'c') {
      Clear(d);
      std::cout << "ok" << std::endl;
    } else if (command[0] == 'e') {
      std::cout << "bye" << std::endl;
      break;
    }
  }
  Clear(d);
  delete d;
  delete[] command;
}

int main() {
  int k;
  std::cin >> k;
  Action(k);
  return 0;
}
