#ifndef AYJ_BINARY_SEARCH_TREE_HH
#define AYJ_BINARY_SEARCH_TREE_HH
#include "AYJ.hh"
#include <stdexcept>

namespace AYJ {

template <class T>
class BinarySearchTreeIterator;

template <class T>
class BinarySearchTree;

template <class T>
class BinarySearchTreeNode {
  BinarySearchTreeNode* parent;
  BinarySearchTreeNode* left;
  BinarySearchTreeNode* right;
  T data;
  bool is_external;
  BinarySearchTreeNode() : parent(nullptr), left(nullptr), right(nullptr), data(T()), is_external(true) {}
  friend class BinarySearchTreeIterator<T>;
  friend class BinarySearchTree<T>;
};

template <class T>
class BinarySearchTreeIterator {
public:
  using Node=BinarySearchTreeNode<T>;
  BinarySearchTreeIterator() : ptr_(nullptr) {}
  BinarySearchTreeIterator(Node* ptr) : ptr_(ptr) {}
  BinarySearchTreeIterator(const BinarySearchTreeIterator& it) : ptr_(it.ptr_) {}

  BinarySearchTreeIterator& operator=(const BinarySearchTreeIterator& it) {
    ptr_ = it.ptr_;
    return (*this);
  }

  bool operator==(const BinarySearchTreeIterator& it) const {
    return ptr_ == it.ptr_;
  }

  bool operator!=(const BinarySearchTreeIterator& it) const {
    return !((*this) == it);
  }

  BinarySearchTreeIterator& operator++() {
    if (ptr_->right->is_external) {
      Node* temp = ptr_->parent;
      while (!temp->is_external && temp->right == ptr_) {
        ptr_ = temp;
        temp = ptr_->parent;
      }
      ptr_ = temp;
    } else {
      ptr_ = BinarySearchTree<T>::left_most(ptr_->right);
    }
    return (*this);
  }

  BinarySearchTreeIterator operator++(int) {
    BinarySearchTreeIterator temp = (*this);
    ++(*this);
    return temp;
  }

  BinarySearchTreeIterator& operator--() {
    if (ptr_->is_external) {
      ptr_ = ptr_->parent;
    } else if (ptr_->left->is_external) {
      Node* temp = ptr_->parent;
      while (!temp->is_external && ptr_ == temp->left) {
        ptr_ = temp;
        temp = ptr_->parent;
      }
      if (!ptr_->is_external) {
        ptr_ = temp;
      }
    } else {
      ptr_ = BinarySearchTree<T>::right_most(ptr_->left);
    }
    return (*this);
  }

  BinarySearchTreeIterator operator--(int) {
    BinarySearchTreeIterator temp = (*this);
    --(*this);
    return temp;
  }

  T& operator*() {
    return ptr_->data;
  }

  T* operator->() {
    return &ptr_->data;
  }

  Node* ptr() {
    return ptr_;
  }
private:
  Node* ptr_;
};

template <class T>
class BinarySearchTree {
public:
  using Node=BinarySearchTreeNode<T>;
  using iterator=BinarySearchTreeIterator<T>;
  BinarySearchTree() : size_(0) {
    root_ = new Node();
    root_->parent = root_;
    root_->left = root_;
    root_->right = root_;
  }

  void insert(const T& data) {
    if (root_->is_external) {
      root_->is_external = false;
      root_->data = data;
      Node* external_node = new Node();
      external_node->right = root_;
      external_node->parent = root_;
      external_node->left = root_;
      root_->left = external_node;
      root_->right = external_node;
      root_->parent = external_node;
      return;
    }
    Node* here = root_;
    Node* new_node = new Node();
    Node* external_node = new Node();
    external_node->left = external_node->right = external_node;
    external_node->parent = new_node;
    new_node->right = new_node->left = external_node;
    new_node->is_external = false;
    new_node->data = data;
    bool left = true;
    while (!here->is_external) {
      if (here->data > data) {
        left = true;
        here = here->left;
      } else {
        left = false;
        here = here->right;
      }
    }
    Node* parent = here->parent;
    new_node->parent = parent;
    if (left) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
  }

  iterator begin() {
    return iterator(left_most(root_));
  }

  iterator end() {
    return iterator(right_most(root_)->right);
  }

  size_type size() const {
    return size_;
  }

  bool empty() const {
    return !size_;
  }

  static Node* left_most(Node* here) {
    while (!here->left->is_external) {
      here = here->left;
    }
    return here;
  }

  static Node* right_most(Node* here) {
    while (!here->right->is_external) {
      here = here->right;
    }
    return here;
  }
private:
  Node* root_;
  size_type size_;
};

}

#endif