#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
};

Node* Add(int key) {
  Node* node = new Node{key, nullptr, nullptr};
  return node;
}

Node* RightRotate(Node* p) {
  Node* ch = p->left;
  p->left = ch->right;
  ch->right = p;
  return ch;
}

Node* LeftRotate(Node* p) {
  Node* ch = p->right;
  p->right = ch->left;
  ch->left = p;
  return ch;
}

Node* Splay(Node* root, int key) {
  if (root == nullptr || root->key == key) {
    return root;
  }

  if (root->key > key) {
    if (root->left == nullptr) {
      return root;
    }

    if (root->left->key > key) {
      root->left->left = Splay(root->left->left, key);
      root = RightRotate(root);
    } else if (root->left->key < key) {
      root->left->right = Splay(root->left->right, key);
      if (root->left->right != nullptr) {
        root->left = LeftRotate(root->left);
      }
    }
    return (root->left == nullptr) ? root : RightRotate(root);
  }
  if (root->right == nullptr) {
    return root;
  }
  if (root->right->key > key) {
    root->right->left = Splay(root->right->left, key);
    if (root->right->left != nullptr) {
      root->right = RightRotate(root->right);
    }
  } else if (root->right->key < key) {
    root->right->right = Splay(root->right->right, key);
    root = LeftRotate(root);
  }
  return (root->right == nullptr) ? root : LeftRotate(root);
}

Node* Insert(Node* root, int key) {
  if (root == nullptr) {
    return Add(key);
  }

  root = Splay(root, key);
  if (key == root->key) {
    return root;
  }

  Node* new_node = Add(key);
  if (key < root->key) {
    new_node->right = root;
    new_node->left = root->left;
    root->left = nullptr;
  } else {
    new_node->left = root;
    new_node->right = root->right;
    root->right = nullptr;
  }
  return new_node;
}

void Next(Node* root, int key, int& curr) {
  if (root != nullptr) {
    int key_root = root->key;
    if (key_root == key) {
      curr = key;
      return;
    }
    if (key_root <= key) {
      Next(root->right, key, curr);
    } else {
      curr = (curr == -1 || curr > key_root) ? key_root : curr;
      Next(root->left, key, curr);
    }
  }
}

void preOrder(Node* root) {
  if (root != nullptr) {
    std::cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

void ClearRec(Node* node) {
  if (node != nullptr) {
    ClearRec(node->left);
    ClearRec(node->right);
    delete node;
  }
}

int main() {
  int n, key;
  std::cin >> n;
  char command;
  bool prev_cmd_next = false;
  int elem_from_next = 0;
  Node* root = nullptr;
  for (int i = 0; i < n; ++i) {
    std::cin >> command >> key;
    if (command == '+') {
      if (prev_cmd_next) {
        key = (key + elem_from_next) % 1000000000;
      }
      root = Insert(root, key);
      prev_cmd_next = false;
    } else {
      elem_from_next = -1;
      Next(root, key, elem_from_next);
      std::cout << elem_from_next << '\n';
      prev_cmd_next = true;
    }
  }
  ClearRec(root);
  return 0;
}