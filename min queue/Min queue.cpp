#include <iostream>

struct Node {
  int elem = 0;
  Node* prev = nullptr;
  Node* next = nullptr;
};

struct Queue {
  Node* tail = nullptr;
  Node* head = nullptr;
  int size = 0;
};

int Size(Queue* q) {
  return q->size;
}

void DequeueMin(Queue*& qMin, int& elem) {
  if (Size(qMin) != 0) {
    Node* toDel = qMin->tail;
    if (Size(qMin) != 1 && qMin->tail != nullptr) {
      qMin->tail = qMin->tail->prev;
    }
    if (toDel != nullptr) {
      elem = toDel->elem;
      qMin->size--;
    }
    delete toDel;
  }
}

void Front(Queue*& q, int& elem) {
  if (Size(q) != 0 && q->tail != nullptr) {
    elem = q->tail->elem;
  } else {
    elem = 0;
  }
}

void Pop(Queue*& q) {
  Node* head = q->head;
  q->head = head->next;
  delete head;
}

void ClearMin(Queue*& qMin) {
  int fictitiousElem;
  while (Size(qMin) != 0) {
    DequeueMin(qMin, fictitiousElem);
  }
}

void EnqueueMin(Queue*& qMin, int elem) {
  Node* newNode = new Node{elem, nullptr, nullptr};
  if (Size(qMin) == 0) {
    qMin->head = newNode;
    qMin->head->prev = newNode;
    qMin->tail = newNode;
    qMin->tail->next = newNode;
  } else {
    int frontElem;
    Front(qMin, frontElem);
    if (elem <= frontElem) {
      ClearMin(qMin);
      qMin->head = newNode;
      qMin->head->prev = newNode;
      qMin->tail = newNode;
      qMin->tail->next = newNode;
    } else {
      if (qMin->head != nullptr) {
        for (; elem < (qMin->head->elem); (qMin->size)--) {
          Pop(qMin);
        }
        qMin->head->prev = newNode;
      }
      newNode->next = qMin->head;
      qMin->head = newNode;
    }
  }
  qMin->size++;
}

void Enqueue(Queue*& q, Queue*& qMin, int elem) {
  Node* newNode = new Node{elem, nullptr};
  EnqueueMin(qMin, elem);
  if (Size(q) == 0) {
    q->head = newNode;
    q->head->prev = newNode;
    q->tail = newNode;
  } else {
    q->head->prev = newNode;
    q->head = newNode;
  }
  q->size++;
}

void Dequeue(Queue*& q, Queue*& qMin, int& elem) {
  if (Size(q) != 0) {
    Node* toDel = q->tail;
    int frontElem, fictitiousElem;
    if (Size(qMin) != 0) {
      Front(qMin, frontElem);
      if (toDel->elem == frontElem) {
        DequeueMin(qMin, fictitiousElem);
      }
    }
    if (Size(q) != 1) {
      q->tail = q->tail->prev;
    } else {
      qMin->tail = nullptr;
    }
    elem = toDel->elem;
    q->size--;
    delete toDel;
  }
}

void Clear(Queue*& q, Queue*& qMin) {
  int fictitiousElem;
  while (Size(q) != 0) {
    Dequeue(q, qMin, fictitiousElem);
  }
  ClearMin(qMin);
}

void Actions(Queue* q, int n) {
  char command[9];
  auto* qMin = new Queue;
  for (int i = 0; i < n; i++) {
    std::cin >> command;
    char firstLiteral = command[0];
    if (firstLiteral == 'e') {
      int elem;
      std::cin >> elem;
      Enqueue(q, qMin, elem);
      std::cout << "ok" << '\n';
    } else if (firstLiteral == 'd') {
      if (Size(q) == 0) {
        std::cout << "error" << '\n';
      } else {
        int deletedElem;
        Dequeue(q, qMin, deletedElem);
        std::cout << deletedElem << '\n';
      }
    } else if (firstLiteral == 'f') {
      if (Size(q) == 0) {
        std::cout << "error" << '\n';
      } else {
        int frontElem;
        Front(q, frontElem);
        std::cout << frontElem << '\n';
      }
    } else if (firstLiteral == 's') {
      std::cout << Size(q) << '\n';
    } else if (firstLiteral == 'm') {
      if (Size(qMin) == 0) {
        std::cout << "error" << '\n';
      } else {
        int frontElem;
        Front(qMin, frontElem);
        std::cout << frontElem << '\n';
      }
    } else if (firstLiteral == 'c') {
      Clear(q, qMin);
      std::cout << "ok" << '\n';
    }
  }
  Clear(q, qMin);
  delete qMin;
}

int main() {
  int n;
  std::cin >> n;
  auto* pq = new Queue;
  Actions(pq, n);
  delete pq;
  return 0;
}
