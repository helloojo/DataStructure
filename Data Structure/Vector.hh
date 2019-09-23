#ifndef AYJ_VECTOR_HH
#define AYJ_VECTOR_HH
#include "AYJ.hh"
#include <stdexcept>

namespace AYJ {

template <class T>
class VectorIterator {
public:
  VectorIterator() : ptr_(nullptr) {}
  VectorIterator(T* ptr) : ptr_(ptr) {}
  VectorIterator(const VectorIterator& it) : ptr_(it.ptr_) {}

  VectorIterator& operator=(const VectorIterator& it) {
    ptr_ = it.ptr;
    return (*this);
  }

  T* ptr() {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  T& operator[](size_type offset) const {
    return ptr_[offset];
  }

  VectorIterator& operator+(size_type offset) {
    return VectorIterator(ptr_ + offset);
  }

  VectorIterator& operator-(size_type offset) {
    return VectorIterator(ptr_ - offset);
  }

  VectorIterator& operator+=(size_type offset) {
    ptr_ += offset;
    return (*this);
  }

  VectorIterator& operator-=(size_type offset) {
    ptr_ -= offset;
    return (*this);
  }

  VectorIterator operator++(int) {
    VectorIterator temp = (*this);
    ++ptr_;
    return temp;
  }

  VectorIterator& operator++() {
    ++ptr_;
    return (*this);
  }

  VectorIterator operator--(int) {
    VectorIterator temp = (*this);
    --ptr_;
    return temp;
  }

  VectorIterator& operator--() {
    --ptr_;
    return (*this);
  }

  bool operator<(const VectorIterator& it) const {
    return ptr_ < it.ptr_;
  }

  bool operator>(const VectorIterator& it) const {
    return ptr_ > it.ptr_;
  }

  bool operator<=(const VectorIterator& it) const {
    return !((*this) > it);
  }

  bool operator>=(const VectorIterator& it) const {
    return !((*this) < it);
  }

  bool operator==(const VectorIterator& it) const {
    return it.ptr_ == ptr_;
  }

  bool operator!=(const VectorIterator& it) const {
    return !((*this) == it);
  }
private:
  T* ptr_;
};

template <class T>
class Vector {
public:
  using iterator=VectorIterator<T>;
  Vector() : size_(0), capacity_(default_capacity) {
    container_ = new T[capacity_];
  }

  Vector(const size_type cnt, const T& val = T()) : size_(cnt), capacity_(cnt) {
    container_ = new T[capacity_];
    for (size_type i = 0; i < size_; i++) {
      container_[i] = val;
    }
  }

  Vector(const Vector& other) {
    size_ = capacity_ = other.size();
    container_ = new T[capacity_];
  }

  ~Vector() {
    delete[] container_;
  }

  Vector& operator=(const Vector& other) {
    if (capacity_ < other.size()) {
      reallocate(other.size(), false);
    }
    size_ = other.size();
    for (size_type i = 0; i < other.size(); i++) {
      container_[i] = other[i];
    }
  }

  T& operator[](const size_type idx) {
    return const_cast<T&>(static_cast<const Vector&>(*this)[idx]);
  }

  const T& operator[](const size_type idx) const {
    return container_[idx];
  }

  bool operator==(const Vector& other) const {
    if (other.size() != size_) {
      return false;
    }
    for (size_type i = 0; i < size_; i++) {
      if (other[i] != container_[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Vector& other) const {
    return !(*this == other);
  }

  bool operator<(const Vector& other) const {
    if (size_ != other.size()) {
      return size_ < other.size();
    }
    for (size_type i = 0; i < size_; i++) {
      if (container_[i] != other[i]) {
        return container_[i] < other[i];
      }
    }
    return false;
  }

  bool operator>(const Vector& other) const {
    if (size_ != other.size()) {
      return size_ > other.size();
    }
    for (size_type i = 0; i < size_; i++) {
      if (container_[i] != other[i]) {
        return container_[i] > other[i];
      }
    }
    return false;
  }

  bool operator<=(const Vector& other) const {
    return !(*this > other);
  }

  bool operator>=(const Vector& other) const {
    return !(*this < other);
  }

  void assign(const size_type cnt, const T& val) {
    if (cnt > capacity()) {
      reallocate(cnt, false);
    }
    size_ = cnt;
    for (size_type i = 0; i < cnt; i++) {
      container_[i] = val;
    }
  }

  T& at(const size_type idx) {
    return container_[idx];
  }

  const T& at(const size_type idx) const {
    return container_[idx];
  }

  void push_back(const T& data) {
    if (size_ == capacity_) {
      reallocate(capacity_ << 1);
    }
    container_[size_++] = data;
  }

  void pop_back() {
    if (size_ == 0) {
      return;
    }
    container_[size_--] = T();
  }

  const T& front() const {
    return container_[0];
  }

  T& front() {
    return const_cast<T&>(
      static_cast<const Vector&>(*this).front()
      );
  }

  const T& back() const {
    return container_[size_ - 1];
  }

  T& back() {
    return const_cast<T&>(
      static_cast<const Vector&>(*this).back()
      );
  }

  size_type size() const {
    return size_;
  }

  size_type length() const {
    return size_;
  }

  size_type capacity() const {
    return capacity_;
  }

  bool empty() const {
    return !size_;
  }


  void clear() {
    for (size_type i = 0; i < size_; i++) {
      container_[i] = T();
    }
    size_ = 0;
  }

  void reserve(size_type capacity) {
    if (capacity_ >= capacity) {
      return;
    }
    reallocate(capacity);
  }

  iterator begin() const {
    return iterator(container_);
  }

  iterator end() const {
    return iterator(container_ + size_);
  }

private:
  T* container_;
  size_type size_;
  size_type capacity_;
  const static size_type default_capacity = 15;
  void reallocate(const size_type capacity, const bool copy = true) {
    capacity_ = capacity;
    T* temp = new T[capacity_];
    if (copy) {
      for (size_type i = 0; i < size_; i++) {
        temp[i] = container_[i];
      }
    }
    delete[] container_;
    container_ = temp;
  }
};

}

#endif