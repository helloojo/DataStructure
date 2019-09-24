#ifndef AYJ_PRIORITY_QUEUE_HH
#define AYJ_PRIORITY_QUEUE_HH
#include "AYJ.hh"
#include "Vector.hh"
#include <stdexcept>
namespace AYJ {

template <class T, class Alloc = Vector<T>, class Comp = less<T>>
class PriorityQueue {
public:
  PriorityQueue() : container_(), compare_(), pos_(1) {
    container_.resize(default_capacity);
  }

  void push(const T& data) {
    if (container_.size() == pos_) {
      container_.resize(pos_ << 1);
    }
    up_heap(pos_++, data);
  }

  void pop() {
    down_heap(container_[--pos_]);
  }

  const T& top() const {
    return container_[TOP];
  }

  size_type size() const {
    return pos_ - 1;
  }

  bool empty() const {
    return pos_ == 1;
  }

private:
  static const size_type default_capacity = 16;
  const int TOP = 1;
  Alloc container_;
  Comp compare_;
  size_type pos_;
  void up_heap(size_type pos, const T& data) {
    size_type parent;
    while (pos != TOP) {
      parent = (pos >> 1);
      if (!compare_(container_[parent], data)) {
        break;
      }
      container_[pos] = container_[parent];
      pos = parent;
    }
    container_[pos] = data;
  }

  void down_heap(const T& data) {
    size_type pos = TOP;
    size_type compare_idx;
    size_type left, right;
    while (pos < pos_) {
      left = (pos << 1);
      right = left + 1;
      if (left >= pos_) {
        break;
      } else if (!compare_(container_[left], container_[right])) {
        compare_idx = left;
      } else {
        compare_idx = (right >= pos_ ? left : right);
      }
      if (!compare_(data, container_[compare_idx])) {
        break;
      }
      container_[pos] = container_[compare_idx];
      pos = compare_idx;
    }
    container_[pos] = data;
  }
};

}

#endif