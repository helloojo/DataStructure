#ifndef AYJ_STACK_HH
#define AYJ_STACK_HH
#include "Vector.hh"
#include <stdexcept>
namespace AYJ {
template <class T, class Alloc = Vector<T>>
class Stack {
public:
  Stack() : container_() {}
  ~Stack() {}
  void push(const T& data) {
    container_.push_back(data);
  }
  void pop() {
    container_.pop_back();
  }
  const T& top() const {
    return container_.back();
  }
  T& top() {
    return const_cast<T&> (
      static_cast<const Stack&>(*this).top()
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