#ifndef AYJ_DOUBLE_LINKED_LIST_HH
#define AYJ_DOUBLE_LINKED_LIST_HH
#include <stdexcept>
#include "AYJ.hh"

namespace AYJ {

template <class T>
class DoubleLinkedListIterator;

template <class T>
class DoubleLinkedList;

template <class T>
class DoubleLinkedListNode {
private:
  DoubleLinkedListNode() : data(T()), next(nullptr), prev(nullptr) {}
  T data;
  DoubleLinkedListNode* next;
  DoubleLinkedListNode* prev;
  friend class DoubleLinkedListIterator<T>;
  friend class DoubleLinkedList<T>;
};

template <class T>
class DoubleLinkedListIterator {
public:
  DoubleLinkedListIterator() : ptr_(nullptr) {}

  DoubleLinkedListIterator(DoubleLinkedListNode<T>* ptr) : ptr_(ptr) {}

  DoubleLinkedListIterator(const DoubleLinkedListIterator<T>& it) : ptr_(it.ptr_) {}

  DoubleLinkedListIterator& operator=(const DoubleLinkedListIterator& it) {
    ptr_ = it.ptr_;
    return (*this);
  }

  DoubleLinkedListIterator operator++(int) {
    DoubleLinkedListIterator<T> temp = (*this);
    if (ptr_ == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr_->next == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr_ = ptr_->next;
    return temp;
  }

  DoubleLinkedListIterator& operator++() {
    if (ptr_ == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr_->next == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr_ = ptr_->next;
    return (*this);
  }

  DoubleLinkedListIterator operator--(int) {
    DoubleLinkedListIterator<T> temp = (*this);
    if (ptr_ == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr_->prev == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr_ = ptr_->prev;
    return temp;
  }

  DoubleLinkedListIterator& operator--() {
    if (ptr_ == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr_->prev == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr_ = ptr_->prev;
    return (*this);
  }

  T& operator*() {
    return ptr_->data;
  }

  T* operator->() {
    return &ptr_->data;
  }

  bool operator==(const DoubleLinkedListIterator& it) {
    return it.ptr_ == ptr_;
  }

  bool operator!=(const DoubleLinkedListIterator& it) {
    return !((*this) == it);
  }

  DoubleLinkedListNode<T>* ptr() const {
    return ptr_;
  }
private:
  DoubleLinkedListNode<T>* ptr_;
};

template <class T>
class DoubleLinkedList {
public:
  using iterator=DoubleLinkedListIterator<T>;
  DoubleLinkedList() : size_(0) {
    head = tail = new DoubleLinkedListNode<T>();
  }

  ~DoubleLinkedList() {
    DoubleLinkedListNode<T>* temp;
    while (head) {
      temp = head;
      head = head->next;
      delete temp;
    }
  }

  const T& front() const {
    return head->data;
  }

  T& front() {
    return const_cast<T&>(
      static_cast<const DoubleLinkedList&>(*this).front()
      );
  }

  void push_front(const T& data) {
    DoubleLinkedListNode<T>* new_node = new DoubleLinkedListNode<T>();
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    ++size_;
  }

  void pop_front() {
    if (head == tail) {
      throw std::runtime_error("Empty List");
    }
    DoubleLinkedListNode<T>* remove_node = head;
    head = head->next;
    head->prev = nullptr;
    delete remove_node;
    --size_;
  }

  const T& back() const {
    return tail->prev->data;
  }

  T& back() {
    return const_cast<T&>(
      static_cast<const DoubleLinkedList&>(*this).back()
      );
  }

  void push_back(const T& data) {
    DoubleLinkedListNode<T>* new_node = new DoubleLinkedListNode<T>();
    new_node->data = data;
    if (tail->prev != nullptr) {
      tail->prev->next = new_node;
    }
    new_node->prev = tail->prev;
    new_node->next = tail;
    tail->prev = new_node;
    if (size_ == 0) {
      head = new_node;
    }
    ++size_;
  }

  void pop_back() {
    if (head == tail) {
      throw std::runtime_error("Empty List");
    }
    DoubleLinkedListNode<T>* remove_node = tail->prev;
    if (head == remove_node) {
      head = tail;
      tail->prev = nullptr;
    } else {
      remove_node->prev->next = tail;
      tail->prev = remove_node->prev;
    }
    delete remove_node;
    --size_;
  }

  iterator begin() const {
    return iterator(head);
  }

  iterator end() const {
    return iterator(tail);
  }

  size_type size() const {
    return size_;
  }

  bool empty() const {
    return head == tail;
  }

  void insert(iterator& it, const T& data) {
    if (it.ptr() == tail) {
      throw std::runtime_error("insert behind tail");
    }
    DoubleLinkedListNode<T>* new_node = new DoubleLinkedListNode<T>();
    new_node->data = data;
    new_node->prev = it.ptr();
    new_node->next = it.ptr()->next;
    it.ptr()->next->prev = new_node;
    it.ptr()->next = new_node;
    size_++;
  }

  iterator remove(iterator& it) {
    DoubleLinkedListNode<T>* remove_node = it.ptr();
    if (remove_node == tail) {
      throw std::runtime_error("cannot remove tail");
    }
    if (head == remove_node) {
      head = tail;
      tail->prev = nullptr;
    } else {
      remove_node->prev->next = remove_node->next;
      remove_node->next->prev = remove_node->prev;
    }
    it = remove_node->next;
    delete remove_node;
    --size_;
    return it;
  }
private:
  size_type size_;
  DoubleLinkedListNode<T>* head;
  DoubleLinkedListNode<T>* tail;
};



}
#endif