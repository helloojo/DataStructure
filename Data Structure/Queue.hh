#ifndef AYJ_QUEUE_HH
#define AYJ_QUEUE_HH
#include "DoubleLinkedList.hh"
#include <stdexcept>

namespace AYJ {
template <class T, class Alloc = DoubleLinkedList<T>>
class Queue {
public:
  Queue() : container_() {}
  ~Queue() {}
  void push(const T& data) {
    container_.push_back(data);
  }
  void pop() {
    container_.pop_front();
  }
  const T& front() const {
    return container_.front();
  }
  T& front() {
    return const_cast<T&> (
      static_cast<const Queue&>(*this).front()
      );
  }
  size_type size() const {
    return container_.size();
  }
  bool empty() const {
    return container_.empty();
  }
private:
  Alloc container_;
};
}


#endif