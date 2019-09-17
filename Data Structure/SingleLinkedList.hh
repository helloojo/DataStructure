#ifndef AYJ_SINGLE_LINKED_LIST_HH
#define AYJ_SINGLE_LINKED_LIST_HH
#include <stdexcept>
#include "AYJ.hh"

namespace AYJ {

template <class T>
class SingleLinkedList;

template <class T>
class SingleLinkedListIterator;

template <class T>
class SingleLinkedListNode {
private:
  SingleLinkedListNode() : data(T()), next(nullptr) {}
  T data;
  SingleLinkedListNode<T>* next;
  friend class SingleLinkedList<T>;
  friend class SingleLinkedListIterator<T>;
};

template <class T>
class SingleLinkedListIterator {
public:
  SingleLinkedListIterator() : ptr(nullptr) {}

  SingleLinkedListIterator(SingleLinkedListNode<T>* ptr) : ptr(ptr) {}

  SingleLinkedListIterator(const SingleLinkedListIterator& it) {
    ptr = it.ptr;
  }

  SingleLinkedListIterator operator++(int) {
    SingleLinkedListIterator temp = (*this);
    if (ptr == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr->next == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr = ptr->next;
    return temp;
  }

  SingleLinkedListIterator& operator++() {
    if (ptr == nullptr) {
      throw std::runtime_error("nullptr Iterator");
    }
    if (ptr->next == nullptr) {
      throw std::out_of_range("End of List");
    }
    ptr = ptr->next;
    return (*this);
  }

  bool operator==(const SingleLinkedListIterator<T>& it) {
    return it.ptr == ptr;
  }
  bool operator!=(const SingleLinkedListIterator<T>& it) {
    return !((*this) == it);
  }

  T& operator*() {
    return ptr->data;
  }

  T* operator->() {
    return &ptr->data;
  }

  SingleLinkedListIterator& operator=(const SingleLinkedListIterator& it) {
    ptr = it.ptr;
    return (*this);
  }
private:
  SingleLinkedListNode<T>* ptr;
};

template <class T>
class SingleLinkedList {
public:
  using iterator=SingleLinkedListIterator<T>;
  SingleLinkedList() : size_(0) {
    head = tail = new SingleLinkedListNode<T>();
  }
  ~SingleLinkedList() {
    SingleLinkedListNode<T>* temp;
    while (head) {
      temp = head;
      head = head->next;
      delete temp;
    }
  }
  bool empty() const {
    return head == tail;
  }
  const T& front() const {
    return head->data;
  }
  T& front() {
    return const_cast<T&>(
      static_cast<const SingleLinkedList&>(*this).front()
      );
  }
  void push_front(const T& data) {
    SingleLinkedListNode<T>* new_node = new SingleLinkedListNode<T>();
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    ++size_;
  }
  void pop_front() {
    if (head == tail) {
      throw std::runtime_error("Empty List");
    }
    SingleLinkedListNode<T>* remove_node = head;
    head = head->next;
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
private:
  SingleLinkedListNode<T>* head;
  SingleLinkedListNode<T>* tail;
  size_type size_;
};
}
#endif
